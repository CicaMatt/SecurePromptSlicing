import java.util.*;
public class Code {
    public static int getValueFromArray(int[] arr,int index){
        return arr[index];
    }
    public static void main (String[] args) {
        int[] id_sequence = {1,2,3,4,5};
        Scanner sc=new Scanner(System.in);
        int index=sc.nextInt();
        System.exit(getValueFromArray(id_sequence,index));
    }
}