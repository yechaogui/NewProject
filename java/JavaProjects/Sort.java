public class MaoPao {
public static void main(String[] args) {
int arr[]={23,12,46,24,87,65,18,14,43,434,65,76};
//int arr[]={23,12,46,24,76};
int k=0;
//ð������
for(int i=0;i<arr.length-1;i++){
for(int j=0;j<arr.length-1;j++){
if(arr[j]<arr[j+1]){
int t=arr[j];
arr[j]=arr[j+1];
arr[j+1]=t;
k++;
}
System.out.print("i="+i+"�ĵ�j="+j+"�ν���\t");
for(int d=0;d<arr.length;d++){
System.out.print(arr[d]+"\t");
}
System.out.println();
}
}

System.out.println("�����Ĵ���Ϊ"+k);

//ѡ������
int l=0;
for(int i=0;i<arr.length-1;i++){
	for(int j=i+1;j<arr.length-1;j++){
		if(arr[i]<arr[j]){
			int t=arr[i];
			arr[i]=arr[j];
			arr[j]=t;
			l++;
	}
	System.out.print("i="+i+"�ĵ�j="+j+"�ν���\t");
for(int d=0;d<arr.length;d++){
	System.out.print(arr[d]+"\t");
}
	System.out.println();
	}
	}
for(int i=0;i<arr.length;i++){
	System.out.print(arr[i]+"\t");
}
System.out.println("�����Ĵ���Ϊ"+l);
}
}