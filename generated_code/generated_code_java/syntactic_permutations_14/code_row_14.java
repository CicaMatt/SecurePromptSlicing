import java.util.Scanner;
public class Hello {
    public static int findValue(int[] id_sequence, int index){
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int i = sc.nextInt();
        return id_sequence[index];
    }
}