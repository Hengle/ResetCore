//
// Created by 35207 on 2018/11/23 0023.
//

#include "gtest/gtest.h"
#include <iostream>
#include <utility>
#include <map>
#include <initializer_list>

using namespace std;

namespace CPP_11_FEATURE_CHAPTER_3 {


    /**
     *
     * �̳й��캯��
     * ��ʹ�û������ͺ�����˼����չ�����캯����
     *
     * ��Ҫע��Ĭ��ֵ���������ɶ�����캯���汾�������
     * ��Ĭ�ϲ����Ĺ��캯������С��
     *
     */
     class ClassA{
     public:
         ClassA(){}
         ClassA(int i){}
         ClassA(double d, int i){};
     };

     class ClassB : ClassA{
     public:
         using ClassA::ClassA; //�̳й��캯��
     };

     class ClassC{
     public:
         ClassC(){}
         ClassC(int i){}
     };

     /**
      * ��̳е����
      */
     class ClassD : ClassA, ClassC {
     public:
         using ClassA::ClassA;
         using ClassC::ClassC;
         ClassD(int i){}    //��ֹ���캯����ͻ
     };

     TEST(CPP_11_FEATURE, CHAPTER_3_DRIVER_CONSTRUCTOR){
        ClassB b(100);  //͸�����õ�A�Ĺ��캯��
     }


     /**
      * ί�ɹ��캯��
      */
     class ClassE{
     public:
         ClassE() { Init(); }

         /**
          * C++98������
          * ClassE(int a) : a(a) { Init(); }
          * ClassE(char* b) : b(b) { Init(); }
          */

         /**
          * C++11������
          * ί�ɹ��캯�������г�ʼ����
          */

         ClassE(int a) : ClassE() { this->a = a; }
         ClassE(char* b) : ClassE() { this->b = b; }

     private:
         int a { 100 };
         char* b { (char*)"aa" };
         void Init(){};
     };

     /**
      * ���Ի�һ��д��
      * ��������ͨ����ʼ�����ʼ������
      */
     class ClassF{
     public:
         //ί�ɹ��캯������Ҳ������ί�ɹ��캯��
         //������Ҫע��ѭ�����õ����
         ClassF() : ClassF(1){}
         ClassF(int i) : ClassF(i, 'a'){}
         ClassF(char b) : ClassF(1, b){}

     private:
         ClassF(int i, char b) : i(i), b(b) {}
         int i;
         char b;
     };

     /**
      * ί�ɹ��캯����ģ�幹�캯�����һ������
      */

     /**
      * ��ֵ���ã��ƶ����������ת��
      *
      * ���һ����������ָ���Ա�Ļ�Ҫ�ر�С�Ŀ������캯���ı�д��
      * ���׳����ڴ�й©
      */

     class ClassG{
     public:
         ClassG() : d(new int(0)) {
             cout << "Construct: " << ++n_cstr << endl;
         }
         //��Ҫ�Լ�ʵ�ֿ������캯����Ĭ�Ͽ������캯�������й©
         ClassG(const ClassG & g) : d(new int(*g.d)) {
             cout << "Copy Construct: " << ++n_cptr << endl;
         }
         /**
          * �ƶ�����
          * ���ֱ��ʹ�ÿ������캯���Ļ�����ɶ�ε���ʱ���캯���Ŀ���
          * ���ʹ���ƶ�����Ļ��򲻻��з�������
          */
         ClassG(ClassG && g) : d(g.d){
             g.d = nullptr;
             cout << "Move construct: " << ++n_mvtr << endl;
         }
         ~ClassG() {
             cout << "Destruct: " << ++n_dstr << endl;
             delete d;
         }
         int getd(){
             return *d;
         }

     private:
         int * d;
         static int n_cstr;
         static int n_dstr;
         static int n_cptr;
         static int n_mvtr;
     };

     int ClassG::n_cstr = 0;
     int ClassG::n_cptr = 0;
     int ClassG::n_dstr = 0;
     int ClassG::n_mvtr = 0;

     ClassG GetClassG(){
         ClassG result;
         cout << "Resource from " << __func__ << endl;
         return result;
     }
     TEST(CPP_11_FEATURE, CHAPTER_3_CONSTRUCT){
         ClassG g = GetClassG();
        cout << "Resource from " << __func__ << endl;
     }

     /**
      * ʵ����C++98/03ʱ�ƶ������Ѿ������ˣ����磺
      * ĳЩ����µĿ������캯����ʡ��
      * ����ָ��Ŀ���
      * ����ƴ��
      * �����ڵ��û�
      */


     /**
      * ��ֵ����ֵ�Լ���ֵ����
      * ���磺a = b + c
      * aΪ��ֵ��b+cΪ��ֵ
      *
      * ���㷺��˵���ǣ�����ȡ��ַ������ֵ������ȡ��ַ������ֵ
      *
      * ��C++11����ֵ���������
      * 1.����ֵ��xvalue, eXpiring Value��
      *     ������������ֵ��������ʳ����ֵ��������ֵ������ֵ��lambda���ʽ��
      *
      * 2.����ֵ(prvalue, Pure Rvalue)
      *     ����ֵ������صı��ʽ��ͨ���ǽ�Ҫ���ƶ��Ķ��󣬱�����ֵ����T&&�ĺ�������ֵ
      *     std::move�ķ���ֵ����ת��ΪT&&������ת�������ķ���ֵ��
      *
      * ����Ŀ��Ա�ʶ����������Ķ�����ֵ��
      *
      * ʵ��������ֵ���ѹ��ɣ��������Ҳ��Ҫ�������͡�
      *
      * ��ֵ���þ��Ƕ�һ����ֵ�������õ����͡�
      */
      ClassG ReturnRvalue(){
         return ClassG();
      }

      TEST(CPP_11_FEATURE_CHAPTER_3, CHAPTER_3_RVALUE){
          cout << endl;
          //ʹ����ֵ�Է���ֵ����
          ClassG && g1 = ReturnRvalue();
          cout << g1.getd() << endl;

          //δʹ����ֵ
          ClassG g2 = ReturnRvalue();
          cout << g2.getd() << endl;
      }


      TEST(CPP_11_FEATURE, CHAPTER_3_RVALUE_ERROR){
        // ��ֵ�����޷��󶨵���ֵ��
        // int c;
        // int && b = c;

        //������ֵ���ÿ��԰���ֵ
        const bool & judgement = true;
        //δʹ����ֵ
        const bool judgement2 = true;
        //ʵ����ʹ�ó�����ֵ����Ҳ���Լ�����ʱ����Ŀ���
      }


      struct Copyable{
          Copyable() = default;
          Copyable(const Copyable & o){
              cout << "copied" << endl;
          }
          Copyable(Copyable&&) noexcept { }
      };

      Copyable ReturnCopyableRvalue(){ return Copyable(); }
      void AcceptVal(Copyable){}
      void AcceptRef(const Copyable & ){}

      TEST(CPP_11_FEATURE, CHAPTER_3_LVALUE_REF){
          cout << endl;
          cout << "Pass by value" << endl;
          AcceptVal(ReturnCopyableRvalue());    //��ʱ������ֵ
          cout << "Pass by ref" << endl;
          AcceptRef(ReturnCopyableRvalue());    //��ʱֵ��Ϊ���ô���
      }

      void AcceptRvalueRef(Copyable&& s){
          Copyable news = std::move(s);
      }
      /**
       * �ж�һ��ֵ�Ƿ�����ֵ
       */
      TEST(CPP_11_FEATURE, CHAPTER_3_IS_REFRENCE){
          cout << is_reference<string &&>::value << endl;
          cout << is_rvalue_reference<string &&>::value << endl;
          cout << is_lvalue_reference<string &&>::value << endl;
      }

      /**
       * ʹ��std::moveǿ��ת��Ϊ��ֵ
       *
       * std::moveʵ���ϲ����ƶ��κζ�����ֻ�ǽ���ֵǿ��ת��Ϊ��ֵ����
       * ���ڣ�
       * static_cast<T&&>(lvalue);
       * �ڵ��ÿ������캯����ʱ���������������е�ֵ���ù���������
       * class Moveable{
       * public:
       *    Moveable(Moveable && m) :
       *        i(m.i), h(std::move(m.h)){
       *        m.i = nullptr;
       *    }
       * private:
       *    int * i;
       *    int h;
       * }
       *
       * ����iΪָ���Ա����hΪ��ͨ�ĳ�Ա
       * �����ʹ��move����������ô�����ĳ�Ա����h����Ϊ��ֵ�������ڽ�����ֱ�����٣�
       * ������Ҫת��Ϊ��ֵ���ӳ���������
       * ���û���ƶ����캯����Ҳ����ֱ��ʹ�ý�����ֵ���õĿ������캯����ֻ�ǻ���
       * �������ʱ����������������̫�����⡣
       */

        /**
         * �ƶ������һЩ��������
         * ������ƶ����캯������Ϊ��
         * Moveable(const Moveable &&)
         * ���߰Ѻ�������Ϊ
         * const Moveable ReturnRValue()
         * ���ᵼ����ʱ���������������޷�ʹ���ƶ����壬������д��ʱ��һ��Ҫ
         * �ų�����Ҫ��const
         *
         *
         */

        /**
         * C++11�п���/�ƶ����캯����3����ʽ��
         * T Object(T &)
         * T Object(const T &)
         * T Object(T &&)
         * ���г�����ֵ�ǿ������캯������ֵ���ð汾�����ƶ�����汾��Ĭ�������
         * ����������ʽ����һ���ƶ����캯����û���õ��򲻻����ɣ�Ĭ���ƶ����캯��
         * ʵ����Ҳֻ�ǰ�λ�������޷������������һЩ�򵥵Ĳ�������Դ�������û���⣬
         * ���������ƶ����ƶ����ǿ�����
         *
         * C++11֮ǰ��๹�춼�ǿ������壬���ֻ���ƶ�����Ļ�Ƚ���Ȥ��
         * ��ʾֻ�ܱ��ƶ������ܱ�������һ�㶼����Դ���ͣ�����ָ�롢�ļ����ȣ�
         * ���ǿ���ͨ��һЩ������ģ�������ж�һ�������Ƿ�����ƶ�
         */
         TEST(CPP_11_FEATURE, CHAPTER_3_MOVE_TYPE_TRAITS){
             cout << is_move_constructible<int>::value << endl;
             cout << is_trivially_move_constructible<int>::value << endl;
             cout << is_nothrow_move_assignable<int>::value << endl;
         }

     /**
      * �����ƶ�����֮����һ��Ӧ�þ��Ǹ����ܵ��û�
      */
      template <typename T>
      void swap(T& a, T& b){
          T tmp(move(a));
          a = move(b);
          b = move(tmp);
      }

      /**
       * �����������ǿ��ƶ������ʹ���ƶ����壬���������ÿ�������
       */
      TEST(CPP_11_FEATURE, CHAPTER_3_MOVE_SWAP){
          cout << endl;
          int a = 100;
          int b = 200;
          swap(a, b);
          cout << "a:" << a << " b:" << b << endl;
      }

      /**
       * �ƶ����캯��Ҫ�����ܷ�ֹ�쳣�ķ���������ƶ�����δ��ɶ��׳��쳣
       * �Ƿǳ�Σ�յġ�
       * ����Ҫ����һ��noexcept�ؼ��֣�
       * ��֤���׳��쳣��ʱ��ֱ����ֹӦ�ö�����ָ������״̬
       *
       * ����֮�⣺
       * ��������RVO(Return Value Optimization)/NRVO(Named Return Vlaue optimization)�Ż�
       * �����RVO/NRVO��
       * ��ô��ReturnValue�����б�������/�ƶ�������ʱ�����Լ�
       * ��ʱ��������/�ƶ�����b�Ķ�����ͨͨû��
       *
       * A ReturnRvalue() { A a(); return a; }
       * A b = ReturnRvalue();
       *
       * b����ֱ��ʹ����a�ĵ�ַ���κεĿ����Լ��ƶ���û�ˣ������������������ʱ����Ч��
       * �����ƶ����廹�Ƿǳ����õġ�
       *
       */

      /**
       * ����ת����ָ�ں���ģ���У���ȫ����ģ��Ĳ��������ͣ����������ݸ�����ģ���е��õ�����һ������
       *
       * template<typename T>
       * void IamForwarding(T t) { IrunCodeActually(t); }
       *
       * ��������ʹ�������������ת�������ǻᵼ����ʱ���󿽱���������ʵ��������
       *
       */

      /**
       *
       * //Ŀ�꺯����Ҫ���ܷǳ�������ֵ����
       * void IrunCodeActually(int& t){}
       *
       * template <typename T>
       * //������ֵ���ã����Խ������е�ֵ
       * void IamForwarding(const T& t)
       * {
       *    //�������޷�����ͨ����ΪĿ�꺯���޷����ܳ�����ֵ����
       *    IrunCodeActually(t);
       * }
       *
       */


      TEST(CPP_11_FEATURE, CHAPTER_3_FORWARDING){

          typedef const int T;
          typedef T& TR;
          //��C++98���޷�����ͨ��
          TR& v = 1;

        /**
         * �����۵�
         * ���Ͷ���   ����������   ʵ������
         * T&        TR          A&
         * T&        TR&         A&
         * T&        TR&&        A&
         * T&&       TR          TR&&
         * T&&       TR&         TR&
         * T&&       TR&&        TR&&
         *
         * ֻҪ��������ֵ��������T&����TR&���վͻ��Ƶ�Ϊ��ֵ����
         */

      }

      /**
       * ͨ�������۵��Լ�forward���԰�����������ת���������͡�
       * ��������κε���ʱ���캯��
       * @param t
       */
    void IrunCodeActually(int && t){}
    void IrunCodeActually(int& t){}
    void IrunCodeActually(const int && t){}
    void IrunCodeActually(const int & t){}


    template <typename T>
    void IamForwarding(T && t)
    {
        /**
         * ʵ����forawrd<T>��static_cast<T&&>�ǵȼ۵ģ�ͨ���۵�����
         * ͨ�������۵����ɰ������ǽ��������ͱ�Ϊ��ֵ����
         */

        IrunCodeActually(forward<T>(t));
    }

    TEST(CPP_11_FEATURE, CHAPTER3_PERFECT_FORWARD){
        int a;
        int b;
        const int c = 1;
        const int d = 0;

        IamForwarding(a);//�ǳ�����ֵ
        IamForwarding(move(b));//�ǳ�����ֵ
        IamForwarding(c);//������ֵ
        IamForwarding(move(d));//������ֵ
    }

    void RunCode(double && m){};
    void RunHome(double && h){};
    void RunComp(double && c){};

    /**
     * ����ת���������ڰ�װ�������е�����ʽ��̵ĸ���
     */
     template<typename T, typename U>
     void PerfectForwardTest(T && t, U& func){
         cout << t << "\tforwarded..." << endl;
         func(forward<T>(t));
     }



     TEST(CPP_11_FEATURE, TEST_PERFECT_FORWARD){
         PerfectForwardTest(1.5, RunCode);
         PerfectForwardTest(3, RunHome);
         PerfectForwardTest(9, RunComp);
     }

     /**
      * C++11��make_pair�Լ�make_unique��ͨ������ת������ʵ�֣�
      * �������ܻ��Ǵ�����϶�����
      */

     /**
      * ��ʾת�������� explicit
      * ��ǰֻ���ڹ��캯�������ã����ڿ����ƹ㵽ת��������
      * C++�е���ʽת���ǳ����׳�������
      */

     class ConvertTo{};
     class Convertable{
     public:
         explicit operator ConvertTo() const { return ConvertTo(); }
     };
    void Func(ConvertTo ct){}
    /**
     * ������ʽת������
     */
    TEST(CPP_11_FEATURE, CHAPTER_3_EXPLICIT){
        Convertable c;
        ConvertTo ct(c);
        //������仰�޷�ͨ��������Ϊ��ʽ�任
        //ConvertTo ct2 = c;
        ConvertTo ct3 = static_cast<ConvertTo>(c);
        //������仰�޷�ͨ��������Ϊ��ʽ�任
        //Func(c);
    }

    /**
     * ��ʼ���б�
     * ���������黹��std�ⶼ�Ѿ�֧�ֵĻ����ų�ʼ��
     */
     TEST(CPP_11_FEATURE, CHAPTER_3_INITIALIZER_LIST){
         int arr1[5] = {0};
         int arr2[] = {1, 2, 3, 4};
         int arr3[] {1, 3, 5};
         vector<int> vec1 {1, 3, 5};
         map<int, float> map1 {{1, 2}, {1, 3}};
     }

     /**
      * C++11�ĸ�ֵ��ʽ
      *
      * �ȺżӸ�ֵ���ʽ
      * int a = 3 + 4;
      *
      * �Ⱥżӻ�����
      * int a = {3 + 4};
      *
      * Բ����
      * int a(3+4);
      *
      * �����ŵĳ�ʼ���б�
      * int a {3 + 4};
      */

     /**
      * ���ǿ����Զ����Լ��ĳ�ʼ���б�Ĺ���
      * ��Ҫ����ͷ�ļ���
      * #include <initializer_list>
      */

     /**
      * ����ʹ�ó�ʼ���б�
      */
     class TestInit{
     public:
         TestInit(initializer_list<pair<string, int>> l){
             auto i = l.begin();
             for(;i != l.end(); ++ i){
                 data.push_back(*i);
             }
         }

     private:
         vector<pair<string, int>> data;
     };

     /**
      * ������ʹ�ó�ʼ���б�
      * @param v
      */
     void InitListFunc(initializer_list<int> v){
         for(auto i = v.begin(); i != v.end(); i ++){
             cout << *i << endl;
         }
     }

     TEST(CPP_11_FEATURE, CHAPTER_3_TEST_INITIALIZER_LIST){
         TestInit init({
             {"hoho", 1},
             {"asd", 2}
         });
         InitListFunc({1, 2, 3});
     }

     /**
      * ����Ҳ����ʹ��[]������
      */
      class TestInitInOperator{
          TestInitInOperator &operator [] (initializer_list<int> l){

          }
          TestInitInOperator &operator =(int v){

          }
      };

      /**
       * ���س�ʼ���б�����
       */
    /**
     * �����������ʱ����
     *
     * vector<int> ReturnInitList(){
     * return {1, 2};
     * }
     */

    /**
     * ��ȷ������const����Ϊ��ͬ�ڷ���������������ᱨ��
     * @return
     */
    const vector<int>& ReturnInitList(){

        return {1, 2};
    }

    /**
     * �����ŵĳ�ʼ����ʽ�����Է�ֹ���ͱ�խ
     * ��ʵ���Ƕ����ȣ��б��ʼ����Ψһһ�ֿ��Է�ֹ������խ�ĳ�ʼ����ʽ
     */
    TEST(CPP_11_FEATURE, CHAPTER_3_NARROWING){
        const int x = 1024;
        const int y = 10;

        char a =  x;
        //����������뱨����Ϊ���ͱ�խ�������ȣ�
        //char c = {x};
        //unsigned char e = {-1};
    }

    /**
     * POD����(Plain Old Data)
     * ��ʾһ�����͵�����
     * Old��������C���Եļ����ԣ�����ʹ��memcpy�Լ�memset���г�ʼ����
     * �����C++��POD��Ϊ��������ĺϼ���
     * ƽ����(trivial)�ͱ�׼����(standard layout)
     */

    /**
     * ʲô��ƽ���ģ�
     * * ӵ��ƽ���Ĺ��캯���Լ�����������Ĭ�Ϲ�������������
     * * ӵ��ƽ���Ŀ��������Լ��ƶ����캯����Ĭ�ϵģ�
     * * ӵ��ƽ���Ŀ�����ֵ������Լ��ƶ���ֵ�������Ĭ�ϵģ�
     * * �������麯���Լ������
     */
     TEST(CPP_11_FEATURE, CHAPTER_3_TRIVIAL){
         //�ж��Ƿ�Ϊƽ����
         cout << std::is_trivial<int>::value << endl;
     }

     /**
      * ʲô�Ǳ�׼���֣�
      * * ���еķѾ�̬��Ա����ͬ�ķ���Ȩ��(public, priveate, protected)
      * * �����ṹ��̳�ʱ���������������֮һ��
      *     1.���������зǾ�̬��Ա����ֻ��һ����������̬��Ա�Ļ���
      *     2.�����зǾ�̬��Ա����������û�зǾ�̬��Ա
      * * ���еĵ�һ���Ǿ�̬��Ա������������಻ͬ
      * * û���麯���������
      * * ���зǾ�̬���ݳ�Ա�����ϱ�׼�������ͣ������Ҳ���ϱ�׼���֣�
      *   ����һ���ݹ�Ķ���
      */

    TEST(CPP_11_FEATURE, CHAPTER_3_IS_POD){
        //�ж��Ƿ�Ϊƽ����
        cout << std::is_pod<int>::value << endl;
    }

    /**
     * ��ôPOD��ɶ�ô���
     * * �ֽڸ�ֵ���԰�ȫ��ʹ��memset��memcpy��POD���ͽ��г�ʼ���Ϳ����Ȳ���
     * * �ṩ��C�ڴ沼�ּ��ݡ�C++���������C�������н�����ΪPOD���͵�������C��
     *   C++ֱ�Ӳ������ǰ�ȫ��
     * * ��֤�˾�̬��ʼ���İ�ȫ��Ч����̬��ʼ���ܶ�ʱ���ܹ���߳�������ܣ�
     *   ��POD���͵Ķ����ʼ���������Ӽ򵥣��������.bbs�Σ��ڳ�ʼ����ֱ�ӱ���ֵ0
     */

    /**
     * ������������
     * ��C++98�в��������г�Ա���ܳ�Ϊ���������ݳ�Ա
     * �⵼���������C�ļ�������ͬ����
     * //Todo
     */

    /**
     * �û��Զ���������
     * ����������Ҫ��ʾ��ɫ��ʱ������ϣ����һ���Լ������������򻯳�ʼ��
     */
     struct RGBA{
         uint8_t r;
         uint8_t g;
         uint8_t b;
         uint8_t a;
         RGBA(uint8_t R, uint8_t G, uint8_t B, uint8_t A=0) :
            r(R), g(G), b(B), a(A) {}
     };

     /**
      * �����Զ���������
      * @param col
      * @param n
      * @return
      */
     RGBA operator "" _COLOR(const char* col, size_t n){
         const char* p = col;
         const char* end = col + n;
         const char *r, *g, *b, *a;
         r = g = b = a = nullptr;
         for(;p != end; ++p){
             if(*p == 'r'){
                 r = p;
             }else if(*p == 'g'){
                 g = p;
             }else if(*p == 'b'){
                 b = p;
             }else if(*p == 'a'){
                 a = p;
             }
         }
         if((r == nullptr) || (g == nullptr) || (b == nullptr))
             throw ;
         else if(a == nullptr){
             return RGBA(atoi(r+1), atoi(g+1), atoi(b+1));
         }else{
             return RGBA(atoi(r+1), atoi(g+1), atoi(b+1), atoi(a+1));
         }
     }

     std::ostream & operator << (std::ostream &out, RGBA& col){
         return out << "r: " << (int)col.r
            << ", g: " << (int)col.g
            << ", b: " << (int)col.b
            << ", a: " << (int)col.a << endl;
     }

     void blend(RGBA&& col1, RGBA&& col2){
         cout << "blend " << endl << col1 << col2 << endl;
     }

     //ʹ���Զ���������
     TEST(CPP_11_FEATURE, CHAPTER_3_LITERAL_OPERATOR){
         blend("r255 g240 b155"_COLOR, "r15 g255 b10 a7"_COLOR);
     }

     struct Watt{ unsigned int v; };
     Watt operator "" _watt(unsigned long long v){
         return { (unsigned int)v };
     }

     TEST(CP_11_FEATURE, CHAPTER_3_LITERAL_OPERATOR_WITH_NUM){
         Watt cap = 1024_watt;
     }

     /**
      * ������ʵ��������һ�����Ƶ�
      * * ���������Ϊ�����ͣ�����������������ֹ�Ƚ���unsigned long long ���� const char*
      *   ���unsigned longlong�޷�����������ʱ���Զ���������ת��Ϊ\0��β���ַ���������char*
      *   �汾���д���
      * * ���������Ϊ����������������������ֻ�ɽ���long double���� const char*Ϊ������
      *   const char*�汾���ȹ���ͬ����
      * * ���������Ϊ�ַ�������������������ֻ�ɽ��� const char*��size_tΪ����
      * * ���������Ϊ�ַ�����������������ֻ�ɽ���һ��charΪ����
      *
      * ������Ҫע��ģ�
      * * ������ʱ operator "" ������û��Զ����׺�����пո�
      * * ��׺�������»��߿�ʼ������ʹ�÷��»��ߺ�׺���û��Զ����ַ���������������б��뾯�棬
      *   ��Ҫ���Ǳ������
      */

     /**
      * �������ֿռ�
      * //Todo
      *
      */

     /**
      * ģ��ı���
      * ����typedef��using��C++11���Ǹ��õ�ѡ��
      */
     TEST(CPP_11_FREATURE, CHAPTER_3_USING_NAME){
         using uint = unsigned int;
         typedef unsigned int UINT;
         cout << is_same<uint, UINT>::value << endl;
     }

     /**
      * using �������ģ����б������������
      */
     template<typename T> using MapString = std::map<T, char*>;
     TEST(CPP_11_FREATURE, CHAPTER_3_TEMPLATE_USING_NAME){
        MapString<int> numberedString;
     }

     /**
      * һ�㻯��SFINEA����
      * ģ�����Ƶ�ʱ�޷�����ƥ���ʱ�򲻻�����������
      * //Todo
      */


}