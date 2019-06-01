//
// Created by ��� on 2018/11/26.
//

#include "gtest/gtest.h"
#include <type_traits>
#include <algorithm>

using namespace std;

namespace CPP_11_FEATURE_CHAPTER_4 {

    /**
     * ģ���е��������Ʒ��Ų����ٷ���������
     */

    /**
     * auto�����Ƶ�
     * ʵ���Ϻ�c#��var���
     * ʹ��stl��ʱ�����������
     *
     * autoͬʱҲ�ܰ��������ж������Ա��⾫�ȶ�ʧ������
     * ��ȻҲ����������������ԡ�
     * ����ֵ���ֵ+1֮�����ͻ���ԭ�������ͣ��޷��������
     *
     * auto�ؼ��ֻ����԰������ǿ�ƽ̨���ڲ�ͬƽ̨�����ʱ�����ֱ��ʹ��auto
     *
     */

    /**
     * autoʹ��ϸ��
     * ����ָ�� auto* �� auto��һ����
     * ���Ƕ������ö��Ա���ʹ��auto&
     *
     * const��volatile ���Ժ�autoһ���ã�
     * ����ͨ��auto�����ı����޷����߳������Լ���ʧ�ԣ�
     * ������������ʱ����Ҫ�����Լ�д��
     */

    TEST(CPP_11_FEATURE, CHAPTER_4_AUTO_USAGE) {
        int x;
        int *y = &x;
        //double foo();
        //int& bar();

        auto *a = &x;   //int*
        auto &b = x;    //int&
        auto c = y;     //int*
        auto *d = y;    //int*
        //auto* e = &foo();   //����ʧ�� ָ���޷�ָ����ʱ����
        //auto& f = foo();    //����ʧ�� �ǳ�����ֵ�޷�����ʱ����
        //auto g = bar(); //int
        //auto& h = bar();//int&


        const auto constVar = 1;    // ӵ�г�����
        auto nonconstVar = constVar;// û�г�����

    }

    /**
     * auto ������
     * * auto�������βΣ������Ҫ���Ͳ���������Ҫ������ģ��
     * * �ṹ��ķǾ�̬��Ա������auto��
     * * auto������������ʽ���� ���磺auto z[3]
     * * ʵ����ģ���ʱ����auto��Ϊģ������ǽ�ֹ��
     *
     * ��ʵ��Щ������C#��Ҳ��һ���������
     */

    /**
     * typeid��decltype
     * RTTI�Ļ�����Ϊÿ�����Ͳ���һ��type_info���͵����ݣ�
     * ����Ա�����ڳ�����ʹ��typeid��ʱ��ѯһ���������͵����֡�
     * C++11���������hash_code�����Ա������
     * ���ظ����͵�Ψһ�Ĺ�ϣֵ���������ͱȽ�
     */

    class White {
    };

    class Black {
    };

    TEST(CPP_11_FEATURE, CHAPTER_4_TYPEID) {
        White a;
        Black b;
        cout << typeid(a).name() << endl;
        cout << typeid(b).name() << endl;

        White c;

        bool a_b_sametype = (typeid(a).hash_code() == typeid(b).hash_code());
        bool a_c_sametype = (typeid(a).hash_code() == typeid(c).hash_code());

        cout << "A == B ? " << a_b_sametype << endl;
        cout << "A == C ? " << a_c_sametype << endl;
    }

    /**
     * RTTIʵ���ϻ���һЩ����ʱ����
     * ����ͨ��ѡ��رգ�ͨ�����ǿ����ڱ�����ȷ�����ͻ����
     *
     */

    /**
     * decltypeҲ���Խ����Ƶ�
     */
    TEST(CPP_11_FEATURE, CHAPTER_4_DECLTYPE) {
        int i = 0;
        decltype(i) j = 0;
        cout << typeid(j).name() << endl;

        float a;
        double b;
        decltype(a + b) c;
        cout << typeid(c).name() << endl;
    }

    /**
     * decltype���Զ���������в���
     */

    enum {
        K1, K2, K3
    } anon_e;
    union {
        decltype(anon_e) key;
        char *name;
    } anon_u;

    struct {
        int d;
        decltype(anon_u) id;
    } anon_s[100];

    TEST(CPP_11_FEATURE, CHAPTER_4_DELTYPE_FOR_NO_NAME_CLASS) {
        decltype(anon_s) as;
        as[0].id.key = decltype(anon_e)::K1;
    }

    /**
     * decltype���ԸĽ�ģ��Ĳ�������
     * ��̬�ı�ģ������
     */
    template<typename T1, typename T2>
    void Sum(T1 &t1, T2 &t2, decltype(t1 + t2) &s) {
        s = t1 + t2;
    }

    /**
     * decltype 4 ׼��
     * * ���e��һ��û�����ŵı�Ǳ��ʽ�������Ա���ʱ��ʽ��
     *   ��ôdecltype(e)������������ʵ������͡�
     *   ���⣬���e��һ�������صĺ���������ʱ�ᱨ��
     * * ����e��������T������e��һ������ֵ����decltype(e)ΪT&&
     * * ����e��������T�����e����ֵ��decltype(e)ΪT&
     * * ����e��������T����decltype(e)ΪT
     *
     * ��õķ������������������г�ʼ������Ϊ��ֵ����������Ҫ��ʼ���ġ�
     * �������׳��� decltype((i)) = d ���Ƶ��޷�����ͨ�������
     */

    /**
     * decltype���ܹ�����cv���Ʒ�(const�Լ�volatile)��
     * ��������Ķ�������const����volatile���Ʒ���ʱ��
     * ʹ��decltype�����Ƶ���*��Ա*����̳�
     */

    /**
     * ׷�ٷ�������
     */

    /**
     * ����д���޷�����ͨ������Ҫͨ��auto������
     * template <typename T1, typename T2>
     * decltype(t1 + t2) Sum(T1& t1, T2& t2){
     *    return t1+t2;
     * }
     * �����д���Զ��Ƶ���������
     */
    template<typename T1, typename T2>
    auto Sum(T1 &t1, T2 &t2) -> decltype(t1 + t2) {
        return t1 + t2;
    }

    /**
     * ���ͺ���Ϊģ���Ƶ��ṩ�˲��ٿ�����
     * ���巵�غ���ָ��ĺ���Ҳ�����
     * ��������д������ͬ�ģ������µ�д����������
     */
    int (*(*pf()))() {
        return nullptr;
    }

    auto pf1() -> auto (*)() -> int (*)() {
        return nullptr;
    }

    /**
     * ��ת��������Ҳ�д�����Ӧ��
     * �����ڲ�ͬ�����·��ز�ͬ��ֵ
     */
    double TestDeclForward(int a) {
        return (double) a + 0.1;
    }

    int TestDeclForward(double b) {
        return (int)b;
    }

    template<typename T>
    auto DoDeclForward(T t) -> decltype(TestDeclForward(t)) {
        return TestDeclForward(t);
    }

    TEST(CPP_11_FEATURE, CHAPTER_4_DECLTYPE_AND_FORWARD) {
        cout << DoDeclForward(2) << endl;
        cout << DoDeclForward(0.5) << endl;
    }

    int ForEachAction(int &e) { cout << e << '\t'; }
    /**
     * ���ڷ�Χ��forѭ��
     */
    TEST(CPP_11_FEATURE, CHAPTER_4_RANGE_FOR) {

        //C++98ʱ��Ҫ����
        int arr[5] = {1, 2, 3, 4, 5};
        int *p;
        for (p = arr; p < arr + sizeof(arr) / sizeof(arr[0]); ++p) {
            cout << *p << '\t';
        }

        //���ǻ�����ʹ��for_each������
        for_each(arr, arr + sizeof(arr) / sizeof(arr[0]), ForEachAction);

        //C++11�������˻��ڷ�Χ��for
        for (int &e : arr) {
            cout << e << '\t';
        }

        //Ҳ����ʹ��auto
        for (auto e : arr) {
            cout << e << '\t';
        }
    }
    /**
     * ��Ҫע����Ƿ�Χforѭ����Ҫ�������begin�Լ�end������
     * ���������ǵ�һ�������һ��Ԫ�صķ�Χ
     * Ҫ�����ʵ��++��==�Ȳ�����
     * ���������С�޷�ȷ���Ļ�Ҳ���޷�ʹ�û��ڷ�Χ��for��
     *
     * �ù��˵������ĳ���ԱӦ��ע�⣬���ڷ�Χ��for���Ѿ��������˵�
     */

}