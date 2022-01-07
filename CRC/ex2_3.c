#include<stdio.h>
#include<math.h>
#include<string.h>

int find_sum(char* in_data) //find sum for data
{
	FILE *fp = fopen("./ex2_3.txt","r");
	int i, sum=0;
	while(fgets(in_data, 9, fp) > 0)
	{
		if(strlen(in_data)==1)
		{
			fgets(in_data, 0, fp);
			continue;
		}
		printf("%s\n", in_data);
		for(i=0;i<8;i++)
			sum += ((int)in_data[i]-48)*(int)pow(2, 7-i);
	}
	fclose(fp);
	return sum;
}

int main()
{
	int i, l, n, sum_t=0, sum_r=0, cnt=0;
	char in_data[8], check_sum_t[16], check_sum_r[16];

	//transmitter
	printf("\nData at Transmitter\n");
	sum_t = find_sum(in_data);
	for(i=0;sum_t>0;i++)
	{
		check_sum_t[i] = '0' + !(sum_t %2); // ! for complement
		sum_t/=2;
	}
	printf("\nCheck Sum at Transmitter:\n");
	for(l=i-1;l>=0;l--)
		check_sum_r[i-1-l] = check_sum_t[l];
	l=i;
	for(i=0;i<l;i++)
		check_sum_t[i] = check_sum_r[i];

	for(i=0;i<l;i++)
		printf("%c",check_sum_t[i]);
	printf("\n");

	//append checksum
	FILE *fp = fopen("./ex2_3.txt","a");
	fputs(check_sum_t, fp);
	fclose(fp);

	//receiver
	printf("\nData at Receiver\n");
	sum_r = find_sum(in_data);
	for(i=0;sum_r>0;i++)
	{
		check_sum_r[i] = '0'+!(sum_r %2); // ! for complement
		sum_r/=2;
	}
	l=i;
	printf("\nSum at Receiver:\n");
	for(i=i-1;i>=0;i--)
	{
		printf("%c", check_sum_r[i]);
		if(check_sum_r[i]=='0')
			cnt++;
	}
	if(l==cnt)
		printf("\nNo Data Loss\n");
	else
		printf("\nData Loss\n");
}