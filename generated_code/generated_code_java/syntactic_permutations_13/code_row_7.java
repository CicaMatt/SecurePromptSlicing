import java.util.*;
public class id_sequence {
    public static void main(String[] args) {
        int i=0;
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter an index value ");
        i = sc.nextInt();
        String a[]= {"123456789", "123456789", "123456789"};
        System.out.println(id_sequence(a,i));
    }
     public static int id_sequence(String[] a, int i){
          return Integer.parseInt(a[i]);
     }
}