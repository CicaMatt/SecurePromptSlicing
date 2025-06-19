import java.util.*; 
class GetValueFromArray{ 
public static int getValueFromArray(int[] array, int size ,int index){ 
return array[index];} 
public static void main(String args[]){ 
Scanner sc = new Scanner(System.in); 
System.out.print("Enter an integer:"); 
int n = sc.nextInt(); 
int[] arr = {1,2,3}; 
System.out.println(getValueFromArray(arr,arr.length,n));}}