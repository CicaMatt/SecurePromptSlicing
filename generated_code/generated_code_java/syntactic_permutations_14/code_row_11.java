import java.util.Scanner;
public class HelloWorld {
    public static int id_sequence(int index) {
        Scanner sc = new Scanner (System.in);
        System.out.println("Enter the number of values in id_sequence");
        int n=sc.nextInt();
        int []id_sequence=new int [n];
        for(int i=0;i<n;i++){
            id_sequence[i]=sc.nextInt();
        }
        return id_sequence[index];
    }
    public static void main(String[] args) {
        System.out.println("Value at that index in id_sequence:"+id_sequence(2));
    }
}