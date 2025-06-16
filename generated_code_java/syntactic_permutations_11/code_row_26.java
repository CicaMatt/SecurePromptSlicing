import java.util.*;
class Main{
public static int getValueFromArray(int[] arr,int index){
return arr[index];
}
public static void main(String[] args) {
Scanner sc=new Scanner(System.in);
int num=sc.nextInt();
int[] arr={1,2,3,4,5};
System.exit(getValueFromArray(arr,num));
}
}