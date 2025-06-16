import java.util.Scanner;
public class Id_sequence {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int idx = sc.nextInt();
        System.out.println("Index is :" +idx);
        String []id_sequence = {"123456", "987654","543210"};
        if(idx <= 3){
            System.out.println("Value at index:" + id_sequence[idx-1]);
        }
    }
}