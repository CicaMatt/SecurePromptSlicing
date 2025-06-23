package com.example.james;
import java.util.*;
public class Code{
    public static String code(int index) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter an index value");
        int id_index = scanner.nextInt();
        String[] id_sequence = {"1046783295", "1082634791", "1048576789", "1087654231", "1046891237"};
        return id_sequence[id_index];
    }
}