//
// Created by dieseldong on 2018/11/28.
//

#include <iostream>
#include "gtest/gtest.h"

using namespace std;

namespace CPP_11_FEATURE_CHAPTER_7 {

    /**
     * ��0��NULL��nullptr
     * NULLָ����int���ͻ����������Բ������ã����¶�����
     */

    void f(char *p) {
        cout << "invoke f(char*) " << endl;
    }

    void f(int) {
        cout << "invoke f(int) " << endl;
    }

    TEST(CPP_11_FEATURE, CHAPTER_7_NULLPTR) {
        //�����char*
        f(nullptr);
        //����int
        f(0);
    }

    /**
     * nullptr_t������������ָ���ֵ�ı���
     * * nullptr_t���͵����ݶ��ǵȼ۵Ĳ�����Ϊһֱ
     * * ����ת��Ϊ��ָ������
     * * ��ʹ�����������
     * * �������ڹ�ϵ���ʽ��ֻ����nullptr_t����ָ�����ͱȽ�
     *   ���ҽ�����ϵ�����Ϊ== <= >=Ϊtrue
     *
     *   ��������д�nullptr��Ҫ��ʾת��������ѡ���ض������غ���
     *
     *   nullptr�Ĵ�С��void*��ͬ
     *   nullptr��(void*)0���ӷ��㣬���������ʽת����������C������void*Ҳ���ԣ�
     *   nullptr����ʵ����һ����ֵ����
     *
     *   һ��ֻ��Ҫ��ס��Ҫ��nullptrȡ��ַ�Ϳ�����
     */

    /**
     * Ĭ�Ϻ����Ŀ���
     *
     * ͨ��default�ؼ��ֿ��������еĺ����ع�ƽ��
     */

    class TwoCstor {
    public:
        TwoCstor() = default;

        TwoCstor(int i) : data(i) {}

    private:
        int data;
    };

    //TwoCstor��һ��POD����
    TEST(CPP_11_FEATURE, CHAPTER_7_DEFAULT_METHOD) {
        cout << endl;
        cout << is_pod<TwoCstor>::value << endl;
    }

    class NoCopyCstor {
    public:
        NoCopyCstor() = default;

        NoCopyCstor(const NoCopyCstor &) = delete;
    };

    TEST(CPP_11_FEATURE, CHAPTER_7_DELETE_METHOD) {
        NoCopyCstor a;
        //�޷�����ͨ��
        //NoCopyCstor b(a);
    }

    /**
     * ʵ����������Ҳ����ʹ��default
     * ���ǿ���ɾ��һЩ�����Ա���һЩ����Ҫ����ʽת����
     * �����齫delete��explicit���ã������������
     */

    void Func(int i) {}

    void Func(char c) = delete;

    TEST(CPP_11_FEATURE, CHAPTER_7_DELETE_CUSTOM_FUNC) {
        Func(3);
        //������޷�����ͨ��
        //Func('a');
    }

    /**
     * ���������Խ���operator new����ֹ�ڶ��Ϸ���ö���
     */
    class NonHeapAlloc {
    public:
        void *operator new(std::size_t) = delete;
    };

    TEST(CPP_11_FEATURE, CHAPTER_7_DELETE_HEAP_ALLOC) {
        NonHeapAlloc nh;
        //�޷�����ͨ��
        //NonHeapAlloc * nhp = new NonHeapAlloc();
    }

    /**
     * ͨ��ɾ�������������������Զ���������ջ�ϵĹ���
     */
    class NonStackAlloc {
    public:
        ~NonStackAlloc() = delete;
    };

    TEST(CPP_FEATURE, CHAPTER_7_DELETE_STACK_ALLOC) {
        //�޷�����ͨ��
        //NonStackAlloc ns;
    }

    /**
     * lambda���ʽ
     * [�����б�](�����б�)�ɱ��� -> ����ֵ{����}
     *
     * �ɱ���Ĭ����const
     */
    TEST(CPP_11_FEATURE, CHAPTER_7_FIRST_LAMBDA){
        cout << endl;
        int girls = 3, boys = 4;
        auto totalChild = [](int x, int y) -> int {
            return x + y;
        };
        cout << totalChild(girls, boys) <<endl;
    }

    /**
     * ��������
     */
    TEST(CPP_11_FEATURE, CHAPTER_7_LAMBDA_CAPTURE_VAR){
        cout << endl;
        int girls = 3, boys = 4;
        auto totalChild = [&girls, boys]() -> int{
            return girls + boys;
        };
        totalChild();
    }
    /**
     * �����б����ʽ��
     * * [var]          ֵ���ݷ�ʽ����
     * * [=]            ֵ����ģʽ�������и�������ı���
     * * [&var]         ���ô��ݷ�ʽ����
     * * [&]            ���ô���ģʽ�������и�������ı���
     * * [this]         ����ǰ��thisָ��
     * * [=, &a, &b]    �����ô��ݲ���a,b��������ֵ����ģʽ
     * * [&, a, this]   ��ֵ���ݲ���a��this�������������ô���ģʽ
     * * [=, a]         �Ѿ���ֵ���ݲ��������б�����a���ظ�����
     * * [&, a]         �Ѿ������ô��ݲ��������б�����&a���ظ�����
     *
     * ��Ҫע������ڿ������������lambda������׽�б����Ϊ�գ�
     * ���Ժ���ͨ������࣬�������ܲ����κεķ��Զ�����
     */

    /**
     * C++������˵���Ƿº�����������Java�еĺ�����
     * ʵ���Ϸº�������һ��lambda���ʽ��ʵ�ַ�ʽ
     * Ҳ��һ���﷨��
     */
}