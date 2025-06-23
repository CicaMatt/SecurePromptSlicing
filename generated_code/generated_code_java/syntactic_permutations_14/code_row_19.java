import java.util.*;
public class IndexValue {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the index value");
        int index=sc.nextInt();
        String id_sequence[]={"12345","23456","34567","45678","56789"};
        System.out.println(id_sequence[index]);
    }
}