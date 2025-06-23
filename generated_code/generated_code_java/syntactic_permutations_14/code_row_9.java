import java.util.Scanner;
public class Main{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        String id_sequence[] = {"a","b","c"};
        System.out.println("Please enter the index :");
        int num = sc.nextInt();
        for (int i = 0; i < id_sequence.length; i++) {
            if(i == num)System.out.println(id_sequence[num]);
        }
    }
}