/*����������
����n��ѧ����m�ſγ̵ĳɼ���ÿ��ѧ������Ϣ��ѧ�š������Լ����Ƴɼ���ɡ���ѧ���Ŀ��Գɼ������й�ͳ�Ʒ���������ӡͳ�Ʊ�
����Ҫ��
1��	ͨ�����������ѧ���Ķ��ſγ̵ĳɼ���������Ӧ���ļ�input.dat��
2��	���ļ�input.dat�е����ݽ��д���Ҫ��������¹��ܣ�
i.	�����ſγ̳ɼ����򣬲�������Ӧ���ļ������
ii.	����ÿ�˵�ƽ���ɼ�����ƽ���ɼ����򣬲������ļ���
iii.������ſγ̵�ƽ���ɼ�����߷֡���ͷ֡�������������60~69��������70~79��������80~89��������90������������
iv.	����������ѧ�Ų�ѯĳ�˵ĸ��ſγɼ����������Ҳ�ܴ���
3��	�������ۡ�
4�� ѡ������  �Ը��Ƴɼ����ò�ͬ��Ȩֵ��
*/

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#pragma warning(disable:4996)

#define MAX 100

/*ѧ�������Ͷ���*/
struct STUDENT	
{
	int studentNo; //ѧ��
	char name[20]; //����
	float scores[3];//���Ƴɼ�
	float ravg_score; //��Ȩ���ƽ���ɼ�
	float avg_score; //����Ȩ��ƽ���ɼ�
};


/*------------------ģ��1 ���롢��ȡƽ����-------------------------------------*/

/*�����Ȩ���ֺܷͲ���Ȩ���ܷ�*/
/*ͬʱ���ø���������ratios���洢������ռȨֵ�ı���,n��ʾѧ������,m��ʾm�ſγ�*/
void getAvgScore(STUDENT students[],float ratios[], int n,int m)
{
	int i, j;
	float sum = 0, rsum = 0;
	for  (i= 0; i < n; i++)
	{
		sum = 0;
		rsum = 0;
		for ( j = 0; j < m; j++)
		{
			sum += students[i].scores[j];
			rsum += students[i].scores[j] * ratios[j];
		}
		students[i].avg_score = sum / m;
		students[i].ravg_score = rsum;
	}
}

/*���������ѧ���Ķ��ſγ̵ĳɼ�*/
/*����n��ʾѧ������*/
void input(STUDENT students[], int n,int m)
{
	printf("                    ������������������������������������������������������������\n");
	int i,j;
	printf("                    ������ѧ����ѧ�š�������1-��ѧ�ɼ���2-Ӣ��ɼ���3-������ɼ�\n");
	printf("                    ������������������������������������������������������������\n");
	for (i = 0; i < n; i++)
	{
		printf("                    �����%d��ѧ������Ϣ��\n",i+1);
		printf("                    ѧ�ţ�\n                    ");
		scanf("%d", &students[i].studentNo);
		printf("                    ������\n                    ");
		scanf("%s", &students[i].name);
		for ( j = 0; j < m; j++)
		{
			printf("                    ��%d�Ƴɼ���\n                    ", j + 1);
			scanf("%f", &students[i].scores[j]);
		}
		printf("                    ������������������������������������������������������������\n");
	}
}

void input_ratios(float rat[])
{
	int i;
	FILE *fp;
	fp = fopen("ratios.data", "wb");
	if (fp == NULL)
	{
		printf("Can't open the file");
	}
	printf("\n\n                    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n");
	printf("                    ���������Ȩ�أ���Ϊ1�Ҵ���0С��1����\n\n");
	while (1)
	{
		printf("                    ��ѧ�ɼ���Ȩ��Ϊ��\n                    ");
		scanf("%f", &rat[0]);
		if (rat[0] >= 0 && rat[0] <= 1)
		{
			break;
		}
		else
		{
			printf("                    ��ѧ�ɼ�Ȩ����������\n\n");
		}
	}
	while (1)
	{
		printf("\n                    Ӣ��ɼ���Ȩ��Ϊ��\n                    ");
		scanf("%f", &rat[1]);
		if (rat[1] >= 0 && rat[1] <= 1 && (rat[1] + rat[0]) <= 1)
		{
			break;
		}
		else
		{
			printf("                    Ӣ��ɼ�Ȩ����������\n\n");
		}
	}
	rat[2] = 1.0 - rat[0] - rat[1];
	for (i = 0; i < 3; i++)
	{
		fwrite(&rat[i], sizeof(float), 1, fp);
		//д��Ȩ��
	}
	fclose(fp);
	printf("\n                    �������ɼ���Ȩ��Ϊ��                    \n                    %.2f\n\n", rat[2]);
	printf("                    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n");
}

/*--------------------------------------------------------------------------------*/



/*------------------ģ��2 �ļ���ȡ��д��-------------------------------------*/

/*���ݴ����ļ�*/
void write(STUDENT students[], int n, const char f_name[])
{
	int i;
	FILE *fp;
	fp = fopen(f_name, "wb");
	if (fp == NULL)
	{
		printf("Can't open the write file");
	}
	//printf("Can't open the ");
	for (i = 0; i < n; i++)
	{
		fwrite(&students[i], sizeof(struct STUDENT), 1, fp);
		//һ��д��һ��ѧ���ĳɼ�
	}
	fclose(fp);
}

/*���ļ���������*/
void read(STUDENT students[], int n,const char f_name[])//
{
	int i;
	FILE *fp;
	fp = fopen(f_name, "rb");
	if (fp == NULL)
	{
		printf("Can't open read the file��");
	}
	for ( i = 0; i < n; i++)
	{
		fread(&students[i], sizeof(struct STUDENT), 1, fp);
	}
}



/*------------------ģ��3 ����-------------------------------------*/

/*���ÿ������򰴸��ſγ̽�������*/
/*k��ʾ��Ŀ�涨��1--��ѧ�ɼ���2--Ӣ�3--�����,4--ƽ���ɼ���5--��Ȩƽ���ɼ���6--ѧ��*/
void exchange(STUDENT *a,STUDENT *b)
{
    STUDENT temp;
	temp = *a;
	*a = *b;
	*b = temp;
}


int Quick_One_Pass(STUDENT stu[], int startIndex, int endIndex,int k)
{
	int left = startIndex;
	//�ѵ�һ��Ԫ����Ϊ��׼Ԫ��
	STUDENT &pivot = stu[startIndex];
	int right = endIndex;
	while (left != right)
	{
		/*�Ƚϸ���Ŀ�ɼ�*/
		if (k >= 1 && k <= 3)
		{
			//����right���ƶ�
			while (left < right && stu[right].scores[k - 1] <= pivot.scores[k - 1])
			{
				right--;
			}
			//left����
			while (left < right && stu[left].scores[k - 1] >= pivot.scores[k - 1])
			{
				left++;
			}
		}

		/*�Ƚ�ƽ���ɼ�*/
		if (k == 4)
		{
			//����right���ƶ�
			while (left < right && stu[right].avg_score <= pivot.avg_score)
			{
				right--;
			}
			//left����
			while (left < right && stu[left].avg_score >= pivot.avg_score)
			{
				left++;
			}
		}

		/*�Ƚϼ�Ȩƽ���ɼ�*/
		if (k == 5)
		{
			//����right���ƶ�
			while (left < right && stu[right].ravg_score <= pivot.ravg_score)
			{
				right--;
			}
			//left����
			while (left < right && stu[left].ravg_score <= pivot.ravg_score)
			{
				left++;
			}
		}

		/*�Ƚ�ѧ��*/
		if (k == 6)
		{
			//����right���ƶ�
			while (left < right && stu[right].studentNo > pivot.studentNo)
			{
				right--;
			}
			//left����
			while (left < right && stu[left].studentNo > pivot.studentNo)
			{
				left++;
			}
		}

		//����left��right����λ�õ�ֵ
		if (left < right)
		{
			exchange(&stu[left], &stu[right]);
		}
	}
	//��left=right ������׼Ԫ�غ͸�λ�ã�left����right����ֵ
	exchange(&stu[left], &pivot);
	return left;
}


void Quick_Sort(STUDENT stu[], int startIndex, int endIndex,int k)
{
	if (startIndex >= endIndex)
	{
		return;
	}
	//pivotIndex����׼Ԫ��
	int pivotIndex = Quick_One_Pass(stu, startIndex, endIndex,k);
	//�Ի�׼Ԫ��ǰ���еݹ�
	Quick_Sort(stu, startIndex, pivotIndex - 1,k);
	//�Ի�׼Ԫ�غ���еݹ�
	Quick_Sort(stu, pivotIndex + 1, endIndex,k);
}

/*--------------------------------------------------------------------------------*/






/*------------------ģ��4 �Ը��ųɼ����з���-------------------------------------*/

int degree(float score)
{
	if (score < 60)
	{
		return 0;
	}
	else if(score >= 60 && score < 70)
	{
		return 1;
	}
	else if (score >= 70 && score < 80)
	{
		return 2;
	}
	else if (score >= 80 && score < 90)
	{
		return 3;
	}
	else if (score >= 90)
	{
		return 4;
	}
}

//�����д���ļ���
void write_analyse_result_score(float result[], const char f_name[])
{
	int i;
	FILE *fp;
	int n = 8;
	fp = fopen(f_name, "wb");
	if (fp == NULL)
	{
		printf("Can't open the write file");
	}
	for (i = 0; i < n; i++)
	{
		fwrite(&result[i], sizeof(float), 1, fp);
		//һ��д��һ����Ŀ�Ľ��
	}
	fclose(fp);
}
//���������
//k==1->math,k==2->english,k==3->cs 
void read_analyse_result_score( const char f_name[],int k)
{
	int i;
	float result[8];
	FILE *fp;
	int n = 8;
	fp = fopen(f_name, "rb");
	if (fp == NULL)
	{
		printf("Can't open the file��");
	}
	for (i = 0; i < n; i++)
	{
		fread(&result[i], sizeof(float), 1, fp);
	}
	if (k == 1)
	{
		printf("\n\n                    -----------------------------��ѧ------------------------------");
	}
	else if (k == 2)
	{
		printf("\n\n                    -----------------------------Ӣ��------------------------------");
	}
	else if (k == 3)
	{
		printf("\n\n                    ----------------------------�����-----------------------------");
	}
	printf("\n\n                    ƽ����\t������\t60~69\t70~79\t80~89\t90~100\t��߷�\t��ͷ�\n");
	printf("                    ");
	for (i = 0; i < 8; i++)
	{
		printf("%.1f\t", result[i]);
	}
}

//���or���ѧ���ĳɼ�
void write_analyse_result_student(STUDENT student, const char f_name[])
{
	int i;
	FILE *fp;
	fp = fopen(f_name, "wb");
	if (fp == NULL)
	{
		printf("Can't open the file");
	}
	//printf("Can't open the ");
	fwrite(&student, sizeof(struct STUDENT), 1, fp);
	//д�����or���ѧ���ĳɼ�
	fclose(fp);
}
//k==1->max,k==2->min
void read_analyse_result_student(const char f_name[],int k)
{
	int i;
	FILE *fp;
	STUDENT student;
	fp = fopen(f_name, "rb");
	if (fp == NULL)
	{
		printf("Can't open the file��");
	}
	fread(&student, sizeof(struct STUDENT), 1, fp);
	if (k == 1)
	{
		printf("\n\n                    �ÿƳɼ���ߵ�ѧ��Ϊ��\n");
		printf("                    ѧ�ţ�\t%d\t������\t%s\n\n", student.studentNo, student.name);
	}
	else if (k == 2)
	{
		printf("\n                    �ÿƳɼ���͵�ѧ��Ϊ��\n");
		printf("                    ѧ�ţ�\t%d\t������\t%s\n\n", student.studentNo, student.name);
		printf("                    ---------------------------------------------------------------\n");
	}

}

void read_all_result()
{
	printf("\n\n                    ======================== ����ͳ�ƽ��==========================");
	read_analyse_result_score("math_result.data", 1);
	read_analyse_result_student("math_stu_max.data", 1);
	read_analyse_result_student("math_stu_min.data", 2);
	read_analyse_result_score("english_result.data", 2);
	read_analyse_result_student("english_result.data", 1);
	read_analyse_result_student("english_result.data", 2);
	read_analyse_result_score("cs_result.data", 3);
	read_analyse_result_student("cs_result.data", 1);
	read_analyse_result_student("cs_result.data", 2);
	printf("\n\n                    ===============================================================\n\n");
}

/*������ſγ̵�ƽ���ɼ�����߷֡���ͷ֡�������������60~69��������70~79��������80~89��������90����������*/
/*nΪѧ������*/
void data_analyse(STUDENT students[],int n)
{
	float math_result[8], english_result[8], cs_result[8];
	STUDENT stu_max[3], stu_min[3];
	int i;
	for ( i = 0; i < 8; i++)
	{
		math_result[i] = 0;
		english_result[i] = 0;
		cs_result[i] = 0;
	}
	for (i = 0; i < n; i++)
	{
		//ÿ���ܳɼ�
		math_result[0] += students[i].scores[0];
		english_result[0] += students[i].scores[1];
		cs_result[0] += students[i].scores[2];

		//������ͳ��
		//��ѧ
		switch (degree(students[i].scores[0]))
		{
		case 0:
			math_result[1]++;
			break;
		case 1:
			math_result[2]++;
			break;
		case 2:
			math_result[3]++;
			break;
		case 3:
			math_result[4]++;
			break;
		case 4:
			math_result[5]++;
		}

		//Ӣ��
		switch (degree(students[i].scores[1]))
		{
		case 1:
			english_result[2]++;
			break;
		case 2:
			english_result[3]++;
			break;
		case 3:
			english_result[4]++;
			break;
		case 4:
			english_result[5]++;
			break;
		}
		//�����
		switch (degree(students[i].scores[2]))
		{
		case 0:
			cs_result[1]++;
			break;
		case 1:
			cs_result[2]++;
			break;
		case 2:
			cs_result[3]++;
			break;
		case 3:
			cs_result[4]++;
			break;
		case 4:
			cs_result[5]++;
			break;
		}
	}
	//���ſ�ͳ����߷֡���ͷ�

	//��ѧ
	Quick_Sort(students, 0, n, 1);
	stu_max[0] = students[0];
	stu_min[0] = students[n - 1];
	math_result[6] = stu_max[0].scores[0];
	math_result[7] = stu_min[0].scores[0];
	 
	//Ӣ��
	Quick_Sort(students, 0, n, 2);
	stu_max[1] = students[0];
	stu_min[1] = students[n - 1];
	english_result[6] = stu_max[1].scores[1];
	english_result[7] = stu_min[1].scores[1];

	//�����
	Quick_Sort(students, 0, n, 3);
	stu_max[2] = students[0];
	stu_min[2] = students[n - 1];
	cs_result[6] = stu_max[2].scores[2];
	cs_result[7] = stu_min[2].scores[2];

	//ƽ����
	math_result[0] = math_result[0] / n;
	english_result[0] = english_result[0] / n;
	cs_result[0] = cs_result[0] / n;

	write_analyse_result_score(math_result, "math_result.data");
	write_analyse_result_student(stu_max[0], "math_stu_max.data");
	write_analyse_result_student(stu_min[0], "math_stu_min.data");

	write_analyse_result_score(english_result, "english_result.data");
	write_analyse_result_student(stu_max[1], "english_stu_max.data");
	write_analyse_result_student(stu_min[1], "english_stu_min.data");

	write_analyse_result_score(cs_result, "cs_result.data");
	write_analyse_result_student(stu_max[2], "cs_stu_max.data");
	write_analyse_result_student(stu_min[2], "cs_stu_min.data");

	printf("\n\n                    ======================== ����ͳ�ƽ��==========================");
	printf("\n\n                    -----------------------------��ѧ------------------------------");
	printf("\n\n                    ƽ����\t������\t60~69\t70~79\t80~89\t90~100\t��߷�\t��ͷ�\n");
	printf("                    ");
	for ( i = 0; i < 8; i++)
	{
		printf("%.1f\t", math_result[i]);
	}
	printf("\n\n                    �ÿƳɼ���ߵ�ѧ��Ϊ��\n");
	printf("                    ѧ�ţ�\t%d\t������\t%s\n", stu_max[0].studentNo, stu_max[0].name);
	printf("\n                    �ÿƳɼ���͵�ѧ��Ϊ��\n");
	printf("                    ѧ�ţ�\t%d\t������\t%s\n\n", stu_min[0].studentNo, stu_min[0].name);
	printf("                    ---------------------------------------------------------------\n");

	printf("\n\n                    -----------------------------Ӣ��------------------------------");
	printf("\n\n                    ƽ����\t������\t60~69\t70~79\t80~89\t90~100\t��߷�\t��ͷ�\n");
	printf("                    ");
	for (i = 0; i < 8; i++)
	{
		printf("%.1f\t", english_result[i]);
	}
	printf("\n\n                    �ÿƳɼ���ߵ�ѧ��Ϊ��\n");
	printf("                    ѧ�ţ�\t%d\t������\t%s\n", stu_max[1].studentNo, stu_max[1].name);
	printf("\n                    �ÿƳɼ���͵�ѧ��Ϊ��\n");
	printf("                    ѧ�ţ�\t%d\t������\t%s\n\n", stu_min[1].studentNo, stu_min[1].name);
	printf("                    ---------------------------------------------------------------\n");

	printf("\n\n                    ----------------------------�����-----------------------------");
	printf("\n\n                    ƽ����\t������\t60~69\t70~79\t80~89\t90~100\t��߷�\t��ͷ�\n");
	printf("                    ");
	for (i = 0; i < 8; i++)
	{
		printf("%.1f\t", cs_result[i]);
	}
	printf("\n\n                    �ÿƳɼ���ߵ�ѧ��Ϊ��\n");
	printf("                    ѧ�ţ�\t%d\t������\t%s\n", stu_max[2].studentNo, stu_max[2].name);
	printf("\n                    �ÿƳɼ���͵�ѧ��Ϊ��\n");
	printf("                    ѧ�ţ�\t%d\t������\t%s\n\n", stu_min[2].studentNo, stu_min[2].name);
	printf("                    ---------------------------------------------------------------\n");
}

/*--------------------------------------------------------------------------------*/




/*------------------ģ��5 ����-------------------------------------*/
//���ַ�����
STUDENT Binary_search(STUDENT stu[], int length, int key)
{
	int low, high, mid;
	STUDENT stu_null;
	stu_null.studentNo = -1;
	low = 0;
	high = length - 1;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (stu[mid].studentNo == key)
		{
			return stu[mid];
		}
		if (stu[mid].studentNo > key)
		{
			high = mid - 1;
		}
		if (stu[mid].studentNo < key)
		{
			low = mid + 1;
		}
	}
	return stu_null;
}
//����ѧ�Ų�ѯĳ�˵ĸ��ſγɼ�
//n��ʾѧ������
void search_Sno(STUDENT stu[],int n)
{
	int no;
	STUDENT stu_result;
	Quick_Sort(stu, 0, n-1, 6);
	printf("\n                    ---------------------------------------------\n");
	printf("\n                    ������Ҫ��ѯͬѧ��ѧ�ţ�\n");
	printf("\n                    ---------------------------------------------\n                    ");
	scanf("%d", &no);
	system("cls");
	stu_result = Binary_search(stu, n, no);
	if (stu_result.studentNo == -1)
	{
		printf("                    \n��ѧ����Ϣ�����ڣ������²��ң�\n");
	}
	else
	{
		printf("\n                    -----------------------------------ѧ����Ϣ��--------------------------------------------\n\n");
		printf("                    ѧ��\t����\t��ѧ�ɼ�\tӢ��ɼ�\t������ɼ�\tƽ����\t\t��Ȩƽ����\n");
		printf("                    %d\t\t%s\t%.1f\t\t%.1f\t\t%.1f\t\t%.1f\t\t%.1f\n", 
			stu_result.studentNo, stu_result.name, stu_result.scores[0],
			stu_result.scores[1], stu_result.scores[2], stu_result.avg_score, stu_result.ravg_score);
		printf("\n                    -----------------------------------------------------------------------------------------\n");
	}
}

/*����������ѯĳ�˵ĸ��ſγɼ����������Ҳ�ܴ���*/
void search_Name(STUDENT stu[], int n)
{
	char name[20];
	int i,flag = 0, count = 0;
	printf("\n                    ---------------------------------------------\n");
	printf("\n                    ������Ҫ��ѯͬѧ��������\n");
	printf("\n                    ---------------------------------------------\n                    ");
	scanf("%s", &name);
	system("cls");
	printf("\n                    -----------------------------------------------ѧ����Ϣ��--------------------------------------------------------\n\n");
	for ( i = 0; i < n; i++)
	{
		if (strcmp(name,stu[i].name) == 0)
		{
			flag = 1;
			count++;
			printf("                    �� %d ��ѧ��:\n\n                    ѧ�ţ�%d\t������%s\t��ѧ�ɼ���%.1f\tӢ��ɼ���%.1f\t������ɼ���%.1f\tƽ���֣�%.1f\t��Ȩƽ����%.1f\n",
				count,stu[i].studentNo, stu[i].name, stu[i].scores[0],
				stu[i].scores[1], stu[i].scores[2], stu[i].avg_score, stu[i].ravg_score);
		}
	}
	if (flag == 0)
	{
		printf("                    ���ҵ�ѧ�������ڣ�");
	}
	printf("\n                    -----------------------------------------------------------------------------------------------------------------\n");
}

/*--------------------------------------------------------------------------------*/


/*------------------ģ��6 ���-------------------------------------*/
void output(STUDENT students[], int n)
{
	printf("\n                    -----------------------------------ѧ����Ϣ��-------------------------------------------------\n");
	printf("                    ѧ��\t����\t��ѧ�ɼ�\tӢ��ɼ�\t������ɼ�\tƽ����\t\t��Ȩƽ����\n");
	for (int i = 0; i < n; i++)
	{
		printf("                    %d\t\t%s\t%.1f\t\t%.1f\t\t%.1f\t\t%.1f\t\t%.1f\n", students[i].studentNo, students[i].name, students[i].scores[0],
			students[i].scores[1], students[i].scores[2], students[i].avg_score, students[i].ravg_score);
	}
	printf("                    ----------------------------------------------------------------------------------------------\n");
}

/*--------------------------------------------------------------------------------*/

/*------------------ģ��7 ���ѧ��-------------------------------------*/

//׷��д�����ѧ��
void add(STUDENT students[], int n, const char f_name[])
{
	int i;
	FILE *fp;
	fp = fopen(f_name, "ab");
	if (fp == NULL)
	{
		printf("Can't open the file");
	}
	//printf("Can't open the ");
	for (i = 0; i < n; i++)
	{
		fwrite(&students[i], sizeof(struct STUDENT), 1, fp);
		//һ��д��һ��ѧ���ĳɼ�
	}
	fclose(fp);
}

//n��ʾ�ļ�����ѧ������
int add_student(int n)
{
	int m;
	STUDENT stu[MAX];
	float ratios[3];
	int i;
	FILE *fp;
	fp = fopen("ratios.data", "rb");
	if (fp == NULL)
	{
		printf("Can't open the file");
	}
	for (i = 0; i < 3; i++)
	{
		fread(&ratios[i], sizeof(float), 1, fp);
	}
	printf("\n\n                    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	printf("                    $����������ѧ������(С��100)��                     $\n                    ");
	scanf("%d", &m);
	printf("\n                    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n");
	input(stu,m,3);
	getAvgScore(stu, ratios, m, 3);
	add(stu, m, "input.data");
	n = m + n;
	return n;
}


/*------------------ģ��8 ����-------------------------------------*/
void first_menu()
{
	int account, pass;
	printf("\n\n                    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	printf("\n                    ^             ��������������                ^\n"); 
	printf("                    ^          �����ߩ��������ߩ�               ^\n");
	printf("                    ^          ������������������               ^\n");
	printf("                    ^          ������������������               ^\n");
	printf("                    ^          �����ש������ס���               ^\n");
	printf("                    ^          ������������������               ^\n");
	printf("                    ^          ���������ߡ�������               ^\n");
	printf("                    ^          ������������������               ^\n");
	printf("                    ^          ������������������               ^\n");
	printf("                    ^          ���������� ѧ���ɼ�              ^\n");
	printf("                    ^          ���������� ����ϵͳ              ^\n");
	printf("                    ^          ������������������               ^\n");
	printf("                    ^          �����������������ǩ�             ^\n");
	printf("                    ^          ��������������������             ^\n");
	printf("                    ^          �����������ש�����               ^\n");
	printf("                    ^          ���ϩϡ����ϩ�                   ^\n");
	printf("                    ^          ���ߩ������ߩ�                   ^\n\n");
	printf("                    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	while (1)
	{
		printf("\n\n                    ^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
		printf("                    $���������Ա�˺ţ�       $\n");
		printf("                     ");
		scanf("%d", &account);
		printf("                    $���������룺             $\n");
		printf("                     ");
		scanf("%d", &pass);
		printf("\n                    ^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n");
		if (account == 111 && pass == 123)
		{
			break;
		}
		else
		{
			printf("                    ������Ϣ�������������룡\n");
		}
	}
	system("cls");
}

int input_menu()
{
	int n, m = 3;
	STUDENT stu[MAX];
	float rat[3];
	printf("\n\n                     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	printf("                    $������ѧ������(С��100)                      $\n                    ");
	scanf("%d", &n);
	printf("\n                    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n");
	input(stu, n, m);
	input_ratios(rat);
	getAvgScore(stu, rat, n, m);
	write(stu, n, "input.data");
	return n;
}

int chose_menu()
{
	int opse;
	printf("                    ********************************************\n");
	printf("                    *                                          *\n");
	printf("                    *      1����ӡ��ѧ������ѧ��               *\n");
	printf("                    *      2����ӡ����ѧ�ɼ�����ѧ��           *\n");
	printf("                    *      3����ӡ��Ӣ��ɼ�����ѧ��           *\n");
	printf("                    *      4����ӡ��������ɼ�����ѧ��         *\n");
	printf("                    *      5����ӡ��ƽ���ɼ�����ѧ��           *\n");
	printf("                    *      6����ӡ����Ȩƽ���ɼ�����ѧ��       *\n");
	printf("                    *      7����ӡ���Ƴɼ�ͳ�ƽ��             *\n");
	printf("                    *      8����ѯ����������ѧ��               *\n");
	printf("                    *      9����ѯ��������������               *\n");
	printf("                    *      0����    ��                         *\n");
	printf("                    *                                          *\n");
	printf("                    ********************************************\n");
	printf("\n\n                    �������ѡ��");
	scanf("%d", &opse);
	while (opse < 0 || opse > 9)
	{
		printf("\n                    �������������������ѡ��\n                    ");
		scanf("%d", &opse);
	}
	return opse;
}

int chose_menu_opse()
{
	int opse;
	printf("\n\n                    ================================================\n");
	printf("                    |                                              |\n");
	printf("                    |      1-����ѡ�����       2-���ѧ��         |\n");
	printf("                    |                  0-��    ��                  |\n");
	printf("                    |                                              |\n");
	printf("                    ================================================\n");
	printf("\n\n                    �������ѡ��");
	scanf("%d", &opse);
	while (opse < 0 || opse > 2)
	{
		printf("\n                    �������������������ѡ��\n                    ");
		scanf("%d", &opse);
	}
	return opse;
}

void main_menu()
{
	int n, m = 3;
	STUDENT stu[MAX];
	float rat[3];
	int opse;
	int flag[7] = { 0,0,0,0,0,0,0 };

	//��ҳ
	first_menu();

	//����ҳ��
	n = input_menu();/*����ѧ������*/

	//n = 7;

	read(stu, n, "input.data");
	//output(stu, n);


	//ѡ��ҳ��
	opse = chose_menu();
	system("cls");

	do
	{	
		switch (opse)
		{
		case 1:
			if (flag[0] == 0)
			{
				printf("\n                    ---------------------------------��ѧ����������-----------------------------------------------\n");
				Quick_Sort(stu, 0, n - 1, 6);
				write(stu, n, "quick_sno.data");
				flag[0] = 1;
			}
			else
			{
				printf("\n                    ---------------------------------��ѧ����������-----------------------------------------------\n");
				read(stu, n, "quick_sno.data");
			}
			output(stu, n);//��ӡδ����ѧ��
			break;

		case 2:
			if (flag[1] == 0)
			{
				printf("\n                    -------------------------------����ѧ�ɼ���������---------------------------------------------\n\n");
				Quick_Sort(stu, 0, n - 1, 1);//��ӡ����ѧ�ɼ�����ѧ��
				write(stu, n, "quick_math.data");
				flag[1] = 1;
			} 
			else
			{
				printf("\n                    -------------------------------����ѧ�ɼ���������---------------------------------------------\n\n");
				read(stu, n, "quick_math.data");
			}
			output(stu, n);
			break;

		case 3:
			if (flag[2] == 0)
			{
				printf("\n                    -------------------------------��Ӣ��ɼ���������---------------------------------------------\n\n");
				Quick_Sort(stu, 0, n - 1, 2);//��ӡ��Ӣ��ɼ�����ѧ��
				write(stu, n, "quick_english.data");
				flag[2] = 1;
			}
			else
			{
				printf("\n                    -------------------------------��Ӣ��ɼ���������---------------------------------------------\n\n");
				read(stu, n, "quick_english.data");
			}
			output(stu, n);
			break;

		case 4:
			if (flag[3] == 0)
			{
				printf("\n                    ------------------------------��������ɼ���������--------------------------------------------\n\n");
				Quick_Sort(stu, 0, n - 1, 3);//��ӡ��������ɼ�����ѧ�� 
				write(stu, n, "quick_cs.data");
				flag[3] = 1;
			}
			else
			{
				printf("\n                    ------------------------------��������ɼ���������--------------------------------------------\n\n");
				read(stu, n, "quick_cs.data");
			}
			output(stu, n);
			break;

		case 5:
			if (flag[4] == 0)
			{
				printf("\n                    -------------------------------��ƽ���ɼ���������---------------------------------------------\n\n");
				Quick_Sort(stu, 0, n - 1, 4);//��ӡ��ƽ���ɼ�����ѧ�� 
				write(stu, n, "quick_avg.data");
				flag[4] = 1;
			}
			else
			{
				printf("\n                    -------------------------------��ƽ���ɼ���������---------------------------------------------\n\n");
				read(stu, n, "quick_avg.data");
			}
			output(stu, n);
			break;

		case 6:
			if (flag[5] == 0)
			{
				printf("\n                    -----------------------------����Ȩƽ���ɼ���������-------------------------------------------\n\n");
				Quick_Sort(stu, 0, n - 1, 5);//��ӡ��ƽ���ɼ�����ѧ�� 
				write(stu, n, "quick_ravg.data");
				flag[5] = 1;
			}
			else
			{
				printf("\n                    -----------------------------����Ȩƽ���ɼ���������-------------------------------------------\n\n");
				read(stu, n, "quick_ravg.data");
			}
			output(stu, n);
			break;

		case 7:
			if (flag[6] ==  0)
			{
				data_analyse(stu, n);//��ӡ���Ƴɼ�ͳ�ƽ��
				flag[6] = 1;
			}
			else
			{
				read_all_result();
			}
			break;
		case 8:
			search_Sno(stu, n);
			break;
		case 9:
			search_Name(stu, n);
			break;
		}
		if (opse != 0)
		{
			opse = chose_menu_opse();
			if (opse == 1)
			{
				system("cls");
				opse = chose_menu();
			}
			else if(opse == 2)
			{
				system("cls");
				n = add_student(n);
				opse = chose_menu();
				read(stu, n, "input.data");
				for (int i = 0; i < 7; i++)
				{
					flag[i] = 0;
				}
			}
			system("cls");
		}
	} while (opse != 0 );
}
/*--------------------------------------------------------------------------------*/

int main()
{
	main_menu();
}