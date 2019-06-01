//
// Created by ��� on 2018/11/28.
//

#include "gtest/gtest.h"
#include <iostream>
#include <cstdarg>

#ifndef WIN32
#include <pthread.h>
#endif

using namespace std;

/**
 * ��������Լ�����Ӳ��������
 */
namespace CPP_11_FEATURE_CHAPTER_6 {

    /**
     * �������ʽ
     * ����ʱ�����ͱ���ʱ����
     *
     * const���������������ʱ�����������Ǳ���ʱ����
     */
    enum BitSet {
        V0 = 1 << 0,
        V1 = 1 << 1,
        V2 = 1 << 2,
        VMAX = 1 << 3,
    };

    /**
     * ͨ��constexpr���԰�������ʹ�ñ��ʽ��ʾ����
     * @return
     */
    constexpr int GetConst() { return 1; }

    template<int i = GetConst()>
    void LikeConst() {

    }

    /**
     * constexpr�Ժ���������Ҫ��
     * * ������ֻ�е�һ��return���
     * * ���������з���ֵ
     * * ��ʹ��ǰ�������ж���
     * * return���ر��ʽ����ʹ�÷ǳ������ʽ�ĺ�����ȫ�����ݣ������Ǹ��������ʽ
     *
     * C++11��constexpr�ǲ������������Զ������͵Ķ����
     * ��ȷ�ķ�ʽ�Ƕ����Զ��峣�����캯��
     */

    struct MyConstType {
        constexpr MyConstType(int x) : i(x) {}

        int i;
    };

    constexpr MyConstType mt = {0};

    /**
     * �������캯���У����������Ϊ��
     * ��ʼ���б�ֻ���г������ʽ����ֵ
     * �������ʽ�����������麯��
     */

    /**
     * �������ʽ������Ӧ��
     * ģ��Ĳ�ȷ���ԣ�ģ�庯����ʵ������������㳣�����ʽ����
     * ��constexpr���Զ����Զ���Ϊ��ͨ����
     */
    struct NonLiteral {
        NonLiteral() { i = 5; }

        int i;
    };

    template<typename T>
    constexpr T ConstExp(T t) {
        return t;
    }

    TEST(CPP_11_FEATURE, CHAPTER6_CONSTEXPR_TEMPLATE) {
        NonLiteral nl;
        NonLiteral nl1 = ConstExp(nl);
        //�޷�ͨ������
        //constexpr NonLiteral nl2 = ConstExp(nl);
        constexpr int a = ConstExp(1);
    }

    /**
     * ͨ���ݹ�ĳ������ʽ������ʵ��������ģ��Ԫ��̵�Ч��
     */
    constexpr int Fibonacci(int n) {
        return (n == 1) ? 1 : ((n == 2) ? 1 : Fibonacci(n - 1) + Fibonacci(n - 2));
    }

    TEST(CPP_11_FEATURE, CHAPTER_6_CONSTEXPR_LOOP) {
        int fib[] = {
                Fibonacci(11),
                Fibonacci(12),
                Fibonacci(13),
                Fibonacci(14),
                Fibonacci(15),
                Fibonacci(16),
        };
        for (int i : fib) {
            cout << i << endl;
        }
    }

    /**
     * ����ʵ����constexpr����һ�����ڱ����������㣬
     * ����ʵ����ģ��Ԫ��̻��Ǹ�ǿһЩ
     */

    /**
     * �䳤ģ��
     * ��ǰ�Ѿ����˱䳤��ͱ䳤��������
     */

    /**
     * �䳤��������
     * ʵ���ϱ䳤������ԭ�����ָ���ƶ���
     * vastart�õ����
     * vaarg�ƶ�ָ�벢���õ�����
     * �����������޷��õ��κβ��������Լ����͵�
     */
    double SumOfFloat(int count, ...) {
        va_list ap;
        double sum = 0;
        va_start(ap, count);
        for (int i = 0; i < count; i++) {
            sum += va_arg(ap, double);
        }
        va_end(ap);
        return sum;
    }

    /**
     * C++�����˸����ִ����ı䳤������ʵ�ַ�ʽ
     * ����tuple��������ģ�峤��
     * std::make_tuple(9.8, 'g', "asdasd")
     */
    template<int ... Elements>
    class TypeA {
    };

    TypeA<1, 2, 3> ntvt;

    template<typename T1, typename T2>
    class TypeB {
    };

    template<typename ... A>
    class TypeC : private TypeB<A...> {
    };

    /**
     * �䳤�����ݹ飬����������ɽ���
     * ������������prolog�����д������
     */
    template<typename ...Elements>
    class tuple;// ����䳤ģ��

    //ƫ�ػ�����
    template<typename Head, typename... Tail>
    class tuple<Head, Tail...> : private tuple<Tail...> {
        Head head;
    };

    template<>
    class tuple<> {
    };

    /**
     * �����͵�д��
     * ʵ����Ҳ����ģ��Ԫ��̵ķ�����
     */
    template<long... Nums>
    struct Multiply;

    template<long Head, long... Tail>
    struct Multiply<Head, Tail...> {
        static const long val = Head * Multiply<Tail...>::val;
    };
    template<>
    struct Multiply<> {
        static const long val = 1;
    };

    TEST(CPP_11_FEATURE, CHAPTER_6_VARIABLE_LENGTH_TEMPLATE) {
        cout << Multiply<1, 2, 3, 4, 5>::val << endl;
    }

    /**
     * �䳤ģ����ף������µط����Խ��в�����չ����
     * ���ʽ
     * ��ʼ�����ʽ
     * ���������б�
     * ���Ա��ʼ���б�
     * ģ������б�
     * ͨ�������б�
     * lambda������׽�б�
     */

    template<typename... T>
    void DummyWrapper(T... t) {}

    template<typename T>
    T pr(T t) {
        cout << t << endl;
        return t;
    }

    template<typename... A>
    void VTPrint(A... a) {
        DummyWrapper(pr(a)...);//���Ϊpr(1), pr(",")...
    }

    TEST(CPP_11_FEATURE, CHAPTER_6_FUNCTION_VARIABLE_ARG) {
        VTPrint(1, "asdas", 1.2);
    }

    /**
     * 'sizeof...' Ҳ��һ���²���
     * ������еĲ�������
     */

    template<class... A>
    void PrintPackSize(A... a) {
        int size = sizeof...(A);
        cout << size << endl;
    }

    TEST(CPP_11_FEATURE, CHAPTER_6_SIZE_OF_PACK) {
        PrintPackSize(1, 2, "asd", 1.22);
    }

    /**
     * ģ���еı䳤ģ�����޷����ݹ�ƫ�ػ��Ͷ���߽��������ػ�������
     */

    /**
     * �䳤ģ�������ת�����ʹ��
     */

    struct A{
        A(){}
        A(const A& a){
            cout << "Copy Constructed " << __func__ << endl;
        }
        A(A&& a){
            cout << "Move Constructed " << __func__ << endl;
        }
    };

    struct B{
        B(){}
        B(const B& b){
            cout << "Copy Constructed " << __func__ << endl;
        }
        B(B&& b){
            cout << "Move Constructed " << __func__ << endl;
        }
    };

    /**
     * �䳤ģ��Ķ���
     */
    template<typename... T>
    struct MultiTypes;

    template<typename T1, typename... T>
    struct MultiTypes<T1, T...> : public MultiTypes<T...> {
        T1 t1;
        MultiTypes<T1, T...>(T1 a, T... b) :
                t1(a), MultiTypes<T...>(b...){
            cout << "MultiTypes<T1, T...>(T1 a, T... b)" << endl;
        }
    };
    template <>
    struct MultiTypes<>{
        MultiTypes<>(){
            cout << "MultiTypes<>()" << endl;
        }
    };

    /**
     * ����ת���ı䳤ģ��
     * @tparam VariadicType
     * @tparam Args
     * @param args
     * @return
     */
    template <template <typename ...> class VariadicType, typename... Args>
    VariadicType<Args...> Build(Args&& ... args){
        return VariadicType<Args...>(std::forward<Args>(args)...);
    }

    /**
     * ���Ǵ�������������Build��Ϊ�䳤��������
     * forward֮��û�п������ģ��ݹ鹹��MultTypes
     */
    TEST(CPP_11_FEATURE, CHAPTER_6_VARIABLE_ARGS_AND_FORWARD){
        cout << endl;
        A a;
        B b;
        Build<MultiTypes>(a, b);
    }

    /**
     * �����ڱ�д���ʱ������б䳤ģ��Ļ������õݹ�����
     */

    /**
     * ԭ��������ԭ�Ӳ���
     * Todo Windows�ϲ�������
     */
    #ifndef WIN32
    //Todo
    #endif



}
