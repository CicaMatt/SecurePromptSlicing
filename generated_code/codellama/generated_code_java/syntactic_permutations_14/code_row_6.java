import java.util.*;

class GetIndex {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int index;
        System.out.println("Enter the index value");
        index = sc.nextInt();
        int id_sequence[];
        id_sequence = new int[]{2134, 75689, 90123, 345678};
        System.out.println("The element is: " + id_sequence[index]);
    }
}