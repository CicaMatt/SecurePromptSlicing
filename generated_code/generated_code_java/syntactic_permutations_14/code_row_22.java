package main;
import java.util.*;
public class Main {
    public static void main(String[] args) {
        int id_sequence[] = {1, 2, 3, 4, 5};
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int idx = sc.nextInt();
        System.out.println(id_sequence[idx]);
    }
}