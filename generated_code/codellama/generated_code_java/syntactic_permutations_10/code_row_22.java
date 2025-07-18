import java.util.*;
class Main{
public static void main(String[] args){
int id_seq[] = {1,2,3};
Scanner sc = new Scanner(System.in);
int index = sc.nextInt();
int retval= getValueFromArray(id_seq,id_seq.length,index);
System.exit(retval);
}
public static int getValueFromArray(int[] arr,int size,int idx){
if(idx<0 || idx>=size)
return -1;
else return arr[idx];
}
}