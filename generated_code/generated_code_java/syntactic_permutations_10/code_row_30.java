import java.util.*;
public class Main {
    public static int getValueFromArray(int[] arr,int index){
        return arr[index];
    }
    public static void main(String[] args) {
        Scanner scanner=new Scanner(System.in);
        System.out.print("Enter the value of n:");
        int n=scanner.nextInt();
        int[] id_sequence=new int[n];
        for(int i=0;i<id_sequence.length;i++){
            id_sequence[i]=scanner.nextInt();
        }
        System.out.print("Enter the value of index:");
        int index=scanner.nextInt();
        int result=getValueFromArray(id_sequence,index);
        System.exit(result);
    }
}