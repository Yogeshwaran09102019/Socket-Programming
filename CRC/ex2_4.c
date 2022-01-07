#include<stdio.h>
#include<string.h>
#include<math.h>

void check(char data_b[], char key_b[], char temp[])
{
	int len_data, len_key,i,j;
	len_data = strlen(data_b)-1;
	len_key = strlen(key_b)-1;

	for(i=0;i<len_key;i++)	//copy first key_len bits to temp
		temp[i] = data_b[i];

	while(i<=len_data+1)
	{
		if(temp[0]=='1')	//first bit is 1
		{
			for(j=0;j<len_key;j++)
				temp[j] = ((temp[j] == key_b[j])?'0':'1');	//XORed
			for(j=0;j<len_key-1;j++)//shift
				temp[j] = temp[j+1];
			temp[j] = data_b[i];
		}
		else	//if first bit is zero
		{
			for(j=0;j<len_key-1;j++)//shift
				temp[j] = temp[j+1];
			temp[j] = data_b[i];
		}
		i++;
	}
}

void main()
{
	int i, n_data, n_key, l, dividend=0, divisor=0, cnt=0;
	char data_b[16], key_b[8], rem[16];
	FILE *fp = fopen("./ex2_4.txt","r");	//open file in read mode
	fgets(data_b, 16, fp); //input data
	fgets(key_b, 8, fp);	//input key
	n_data = strlen(data_b)-1;	//length of data
	n_key = strlen(key_b)-1;	//length of key
	fclose(fp);	//close file

	l=n_data+n_key-1;	//legth after padding zeros
	for(i=n_data;i<l;i++)
		data_b[i] = '0';	//pad zeros

	printf("Data to transmit:\n");
	for(i=0;i<l;i++)
		printf("%c", data_b[i]);

	printf("\n\nKey :\n");
	for(i=0;i<n_key;i++)
			printf("%c", key_b[i]);
	printf("\n");

	check(data_b, key_b, rem);	//mod-2 binary division
	
	for(i=n_data;i<l;i++)
		data_b[i] = rem[i-n_data];

	printf("\nTransmitted Data :\n");
	for(i=0;i<l;i++)
		printf("%c", data_b[i]);

	check(data_b, key_b, rem);

	printf("\n\nReceived Data :\n");
	for(i=0;i<l;i++)
		printf("%c", data_b[i]);

	for(i=0;i<n_key;i++)
		printf("%c", rem[i]);

	for(i=0;i<n_key-1;i++)
	{
		if(rem[i]!='0')
		{
			printf("\n\nData is Lost at Receiver\n");
			return;
		}
	}
	printf("\n\nNo data Loss at Receiver\n");
}