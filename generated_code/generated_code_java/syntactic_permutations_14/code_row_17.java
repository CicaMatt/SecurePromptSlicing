import java.util.*;

class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter an index for id_sequence");
        int index = sc.nextInt();
        String[] id_sequence = {"A50", "B92", "C13"};
        System.out.println("Value at the given index is: "+id_sequence[index]);
    }
}