//
// Created by ��� on 2019/2/3.
//

#include "gtest/gtest.h"
#include <setjmp.h>
#include <stdio.h>

namespace LearningC {


    jmp_buf ebuf;
    //����long jmp
    TEST(JMP, TRY){
        int i;
        printf("\n");
        printf("1 ");
        i = setjmp(ebuf);
        printf("i = %d\n",i);//ע�����������
        if (i == 0){
            printf("2 ");
            longjmp(ebuf, 3);//����setjmpִ�е�
            printf("This will not be printed.");//ע�����������
        }
        printf("%d", i);
    }

    
}
