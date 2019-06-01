//
// Created by dieseldong on 2018/11/27.
//

#include "gtest/gtest.h"
#include <iostream>
#include <memory>

using namespace std;

namespace CPP_11_FEATURE_CHAPTER_5{

    /**
     * ö��������C++98����ȫ�ֵ����׷�����ͻ��
     * ���Ҳ�ͬ�ı����������Ĵ�С��һ�������ײ�����ֲ����
     *
     * ��������з�װ���������ռ������Ⱦ��
     * ��������Լ���װ����֮�����������⣺
     * * ��������
     * * ����POD����
     * * �����޷�����Ĵ��������ܿ���
     *
     * ������C++11��ʹ��ǿ����enum����
     * ������C++11�п���ָ����������
     */

    enum class TestEnum : int {
        ENUM_1,
        ENUM_2,
        ENUM_3};

    TEST(CPP_11_FEATURE, CHAPTER_5_STATIC_ENUM){
        cout << (int)TestEnum::ENUM_1 << endl;
    }


    /**
     * ���ڴ��������ָ������������
     *
     * �������ڴ�����ʱ�򾭳������������⣺
     * * Ұָ��
     * * �ظ��ͷ�
     * * �ڴ�й©
     */

    /**
     * ��C++98����auto_ptr��Ϊ����ָ�룬������ȱ�㣺
     * * �����Ƿ���һ����ֵ
     * * ���ܵ���delete[]
     *
     * C++11�����滻Ϊ��unique_ptr��shared_ptr�Լ�weak_ptr
     */

    TEST(CPP_11_FEATURE, CHAPTER_t_SMART_POINTER){

        unique_ptr<int> up1(new int(11));

        //unique_ptr������ֵ
        //unique_ptr<int> up2 = up1;

        cout << *up1 << endl;

        unique_ptr<int> up3 = move(up1);//����up3��Ψһ������ָ��

        cout << *up3 << endl;
        //����ʱ����
        //cout << *up1 << endl;

        up3.reset();    //��ʽ�ͷ��ڴ�
        up1.reset();    //��ʽ�ͷ��ڴ�

        //����ʱ����
        //cout << *up3 << endl;

        shared_ptr<int> sp1(new int(22));
        shared_ptr<int> sp2 = sp1;

        cout << *sp1 << endl; //22
        cout << *sp2 << endl; //22

        sp1.reset();
        cout << *sp2 << endl; //22

    }

    /**
     * unique_ptr��shared_ptr����ǰ����һ�£��������ڴ湲���ϻ�����һ�������
     * unique_ptr���ڴ�ֱ�Ӱ󶨣����ܹ����ڴ档
     * ���ʹ��move��Ὣ�ڴ��ƶ�����һ��ָ���ϡ�ԭ����ָ����޷�ʹ�á�
     *
     * unique_ptrɾ���˿������캯�����������ƶ����캯�������Թ���֮����ֵ���󼴱���ȡ��
     *
     * shared_ptr��������������ӵ��ͬһ�ѷ��������ڴ档�ڲ�ʹ�����ü�����
     * ����һ�������������Ȩ��������ʲôӰ�죬ֻ��������Ϊ0��ʱ��Ż��ͷ��ڴ档
     *
     */

    /**
     * ����ָ���л���һ��weak_ptr���࣬������ָ��shared_ptrָ��ָ����ڴ浫��ӵ�иö���
     * ���ָ��Ķ����Ѿ�ʧЧ�򷵻ؿ�ָ�롣
     *
     * �������weak_ptr��lock������᷵��һ��shared_ptr���÷�Ҳ����ͬ�ˡ�
     *
     * ʹ�÷�ʽ���¡�
     *
     *
     */

    void CheckWeakPtr(weak_ptr<int> &wp){
        shared_ptr<int> sp = wp.lock();
        if(sp != nullptr){
            cout << "still " << *sp << endl;
        }
        else{
            cout << "pointer is invalid." << endl;
        }
    }

    TEST(CPP_11_FEATURE, CHAPTER_5_WEAK_PTR){

        cout << endl;

        shared_ptr<int> sp1(new int(22));
        shared_ptr<int> sp2 = sp1;

        weak_ptr<int> wp = sp1;
        cout << *sp1 << endl;   //22
        cout << *sp2 << endl;   //22
        CheckWeakPtr(wp);

        sp1.reset();
        cout << *sp2 << endl;   //22
        CheckWeakPtr(wp);

        sp2.reset();
        CheckWeakPtr(wp);

    }

    /**
     * ����ָ���ܹ��ȽϺõؽ����ڴ����������Ҫ�������Ǻܶ��ģ�
     * ���Ի�����������
     *
     * ��ʵ���ϻ�û��ɶ������ʵ������С֧�ֵ���������
     */
}