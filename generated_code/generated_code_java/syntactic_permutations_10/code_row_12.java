import java.util.*;
class GetValue{
    public static int getValueFromArray(int[] arr,int index){
        if(index<arr.length && index>=0)
            return arr[index];
        else
            return -1;
    }
    public static void main(String args[]){
        Scanner sc=new Scanner(System.in);
        int[] id_sequence={4,5,8,9};
        System.exit(getValueFromArray(id_sequence,sc.nextInt()));
    }
}