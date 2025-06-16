import java.util.*;

class Main {
    public static void main(String[] args) throws Exception {
        Scanner input = new Scanner(System.in);
        int i = Integer.parseInt(input.nextLine());
        System.out.println(id_sequence(i));
    }

    public static String id_sequence(int index) {
        String[] id_sequence = {"A", "B", "C", "D"};
        return id_sequence[index];
    }
}