#include "FFTMultiplier.h"
#include "cassert"

#define ASSIGN(_array,x,start,num) do{for(int i =start;i< num;++i) _array[i] = x;}while(0)
#define COPY(_array,_assigner,num) ASSIGN(_array,_assigner[i],0,num)

FFTMultiPlier::FFTMultiPlier(const BigInteger& lhs, const BigInteger& rhs){

	assert(lhs.WIDTH == rhs.WIDTH);
	//����lhs��rhs���BASE=10000�Ľ��
	if (lhs.WIDTH != 4){
		//ASize = lhs.length() << 1;
		//BSize = rhs.length() << 1;
		ACoef = Vectype();
		BCoef = Vectype();
		Convert_Base(ACoef, lhs);//��ACoef�����ڴ沢��ת��
		Convert_Base(BCoef, rhs);
	}
	ASize = ACoef.size();
	BSize = BCoef.size();
	auto len = ASize + BSize;
	FFTLength = 2;
	while (FFTLength < len)
		FFTLength <<= 1;

	
	ArrayFFT0 = Vectype(2 * FFTLength);//�洢lhs��FFT���
	ArrayFFT1 = Vectype(2 * FFTLength);//�洢rhs��FFT���
	Result = Vectype(len,0);
	}

void FFTMultiPlier::Convolution(const RefVec A, const RefVec B, RefVec C)
{
	long i;
	Real tmpR, tmpI;

	for (i = 0; i<FFTLength; i++) {
		tmpR = A[2*i]*B[2*i] - A[2*i+1]*B[2*i+1];
		tmpI = A[2*i]*B[2*i+1] + A[2*i+1]*B[2*i];
		C[2*i] = tmpR;
		C[2*i+1] = tmpI;
	}
}
BigInteger FFTMultiPlier::MulWithFFT(){
	FFTFunctor F(FFTLength);
	F.fft(ACoef, ArrayFFT0, 1);
	F.fft(BCoef, ArrayFFT1, 1);
	vector<Real> CovResult(FFTLength*2,0);
	Convolution(ArrayFFT0, ArrayFFT1,CovResult);//ת�����
	F.InverseFFT(CovResult, Result);
	UpdateResult( );
	return BigInteger(Result,ResultSize);
}
void FFTMultiPlier::Convert_Base( RefVec Ret, const BigInteger& lhs)
{	
	auto len = lhs.length();
	assert(len > 0);
	Ret.reserve(lhs.length() << 1);
	if (lhs.WIDTH != 4){
		auto s = lhs.s;
		for (size_t i = 0; i < len - 1; ++i){
			Ret.push_back( (*s)[i] % FFTBase);
			Ret.push_back((*s)[i] / FFTBase);
		}
		auto re = (*s)[len - 1];
		auto remain = re % FFTBase;
		Ret.push_back(remain);
		if (re > FFTBase)
			Ret.push_back(re / FFTBase);

	}
}
//������λ
void FFTMultiPlier::UpdateResult()
{
	assert(Result.size() > 0);
	//�ϲ�
	long  carry = 0;
	for (size_t j = 0; j < Result.size(); ++j){
		auto tmp = Result[j] + carry;
		carry = tmp/FFTBase;
		Result[j] = tmp - carry*FFTBase;
	}
	int i = Result.size() - 1;
	while (i >= 0 && Result[i] == 0) { --i; }
	ResultSize = i>=0 ? i + 1:1 ;//ȥ��0���size
}

FFTMultiPlier::~FFTMultiPlier(){

}