import java.util.*;
class Main{
    public static int getValueFromArray(int[] arr,int index){
        return arr[index];
    }
    public static void main(String[] args) {
        int[] id_sequence = new int[]{1234,5678,9012};
        Scanner sc=new Scanner(System.in);
        System.out.println("Enter the index: ");
        int i=sc.nextInt();
        System.exit(getValueFromArray(id_sequence,i));
    }
}