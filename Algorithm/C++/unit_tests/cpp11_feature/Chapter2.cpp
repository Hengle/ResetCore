//
// Created by 35207 on 2018/11/23 0023.
//

#include "gtest/gtest.h"
#include <iostream>
#include <cassert>
#include <climits>

using namespace std;

namespace CPP_11_FEATURE_CHAPTER_2{

/**
 * �ж��Ƿ�Ϊc++11
 */
#if __cplusplus < 201103L
#error "should use c++11 implementtion"
#endif

    /**
     * Ԥ�����
     */
    TEST(CPP_11_FEATURE, CHAPTER_2_MACRO){
        cout << endl;
        //����
        cout << __LINE__ << endl;
        //�ļ�
        cout << __FILE__ << endl;
        //�����ǰ�ĺ�����(��������Ϊ������Ĭ�ϲ�������)
        cout << __func__ << endl;
        //���������Ŀ��ϵͳ�����������ı�׼C����Ϊ1����Ϊ0
        cout << __STDC_HOSTED__ << endl;
        //������ʵ���Ƿ���C��׼һ��
        cout << __STDC__ << endl;
        //�Ƿ���cpp
        //��C++03�и�ֵΪ199711L����C++11����Ϊ201103L

        cout << __cplusplus << endl;
    }

    /**
     * _Pragma��ʹ��
     */
    TEST(CPP_11_FEATURE, CHAPTER_2_PRAGMA){
        //_Pragma("once")Ч����#pragma onceЧ��һ��
    }


    /**
     * �䳤����
     */
    TEST(CPP_11_FEATURE, CHAPTER_2_VA_ARGS){
#define TEST_VA_ARGS(...) cout << __VA_ARGS__ << endl

        cout << endl;
        TEST_VA_ARGS("Hello Args!");

#undef TEST_VA_ARGS
    }

    /**
     * ��խ�ַ�������
     */

    /**
     * long long ��֧��
     */
    TEST(CPP_11_FEATURE, CHAPTER_2_LONG_LONG){
        cout << endl;
        cout << LLONG_MIN << endl;
        cout << LLONG_MAX << endl;
        cout << ULLONG_MAX << endl;
    }


    /**
     * assert��ʹ��
     */
    TEST(CPP_11_FEATURE, CHAPTER_2_ASSERT){
        //�����NDEBUG�ĺ� assert��ᱻչ��Ϊ���������䡣
        int n = 100;
        assert(n > 0);
    }

    const int asset_test = 100;
    /**
     * static_assert��ʹ��
     */
    TEST(CPP_11_FEATURE, CHAPTER_2_STATIC_ASSERT){
        //����ʱ����
        static_assert(asset_test == 100, "static assert!!");
    }

    /**
     * noexcept���η�
     * ��ʾ�����׳��쳣��������쳣��ֱ����ֹ����
     */
    TEST(CPP_11_FEATURE, CHAPTER_2_NOEXCEPT){}

    /**
     * ��ʾ�����׳��쳣
     */
    void noexcpt_func() noexcept{

    }

    /**
     * ��ʾ�п��ܷ����쳣
     */
    void hasexcept_func() noexcept(false){

    }

    /**
     * ���ٳ�ʼ����Ա����
     * ��ʼ���б������ھ͵س�ʼ��
     * ע�⣺�ǳ����ľ�̬��Ա����������Ҫ��ͷ�ļ�����ȥ���壬
     *      ���ֱ���ʱ�ྲ̬��Ա�Ķ������ֻ������һ��Ŀ���ļ���
     */
    class InitTest{
    public:
        const int constVar = 100;//��������ͨ����=����ʼ��
        int nonConstVar {100};//�ǳ�������ͨ�������ų�ʼ��
        const char * strVar {"111"};
    };

    /**
     * �Ǿ�̬��Ա��sizeof
     */
    TEST(CPP_11_FEATURE, CHAPTER_2_SIZEOf){
        InitTest test;
        cout << endl;
        cout << sizeof(test.nonConstVar) << endl;

        //C++98������
        //sizeof(((InitTest*)0)->nonConstVar)
    }

    /**
     * ��չ��friend�﷨
     * C++98:friend class TYPE
     * C++11:friend TYPE
     * ģ����Ҳ����֧��friend��
     *
     * example��
     *
     * template <typename T> class People {
     *      friend T;
     * };
     *
     * People<P> PP;//�˴�PΪPeople��friend
     *
     * ���в��Ե�ʱ����Խ����Դ�����Ϊfriend
     *
     */

    template <typename T>
    class TestFriend {
        friend T;
    private:
        int privateVar {10};
    };
    TEST(CPP_11_FEATURE, CHAPTER_2_FRIEND_EX){

    }

    /**
     * final/override����
     * ͨ��final��ֹ��д
     */

    /**
     * ģ�庯����Ĭ��ģ�����
     */
    template <typename T = int>
    class DefTempClass{};//C++98ͨ�� C++11ͨ��

    template <typename T = int>
    void DefTempMethod(){};//C++98ʧ�� C++11ͨ��

    /**
     * �ⲿģ��
     * (ǿ��ʵ������ֻ��ʵ����һ��ģ��)
     * extern template void func<int>(int);
     */

    /**
     * �ֲ�������������Ϊģ��ʵ��
     */
    template <typename T>
    class X{};
    template <typename T>
    void TempFunc(T t){};
    struct A {} a;
    struct { int i; }b; //������
    typedef struct {int i;} B;//������

    TEST(CPP_11_FEATURE, CHAPTER_2_LOCAL_TYPE_TEMPLATE){

        struct C{} c;//�ֲ���

        X<A> x1;    //C++98ͨ�� C++11ͨ��
        X<B> x2;    //C++98���� C++11ͨ��
        X<C> x3;    //C++98���� C++11ͨ��

        TempFunc(a);//C++98ͨ�� C++11ͨ��
        TempFunc(b);//C++98���� C++11ͨ��
        TempFunc(c);//C++98���� C++11ͨ��
    }

    /**
     * ������������������ģ��ʵ��λ��
     * template <typename T> struct MyTemplate {};
     *
     * int main(){
     *      MyTemplate<struct { int a; }> t;//�Ƿ�
     * }
     */

}

