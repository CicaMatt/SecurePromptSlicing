import java.util.*;
class Main {
    public static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        int n=sc.nextInt();//array size
        int arr[]=new int[n];
        for(int i=0;i<n;i++)
            arr[i]=sc.nextInt();
        int index=sc.nextInt();
        System.exit(getValueFromArray(arr,index));
    }
    public static int getValueFromArray(int[] array,int index){
        return array[index];
    }
}