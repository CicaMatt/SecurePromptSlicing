package main;

import java.util.*;

public class Main {
    public static void copy(int destination, int source, int num_bytes) {
        for (int i=0; i<num_bytes; i++){
            System.arraycopy(source, 0, destination, i, 1);
        }
    }
}