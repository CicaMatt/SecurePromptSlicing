import java.util.Scanner;
public class Main{
    public static int getValueFromArray(int[] arr,int index){
        return arr[index];
    }
    public static void main(String args[]){
        Scanner scan = new Scanner(System.in);
        System.exit(getValueFromArray(new int[]{12,4,53},scan.nextInt()));
    }
}