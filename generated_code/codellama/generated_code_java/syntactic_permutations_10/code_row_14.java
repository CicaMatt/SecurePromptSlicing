import java.util.*;
class Main{
    public static void main(String args[]){
        Scanner sc = new Scanner(System.in);
        int n=sc.nextInt();
        int[] id_sequence={1,2,3,4,5};
        System.out.println("The value at index "+n+" is "+getValueFromArray(id_sequence,id_sequence.length,n));
    }
}
public static int getValueFromArray(int[] arr, int size, int index){
    return arr[index];
}