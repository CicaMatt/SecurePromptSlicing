package com.mycompany.app;
public class App {
    public static void main(String[] args) {
        int[] id_sequence = {1, 2, 3, 4};
        int index;
        Scanner in = new Scanner(System.in);
        System.out.println("Enter the index value: ");
        index=in.nextInt();
        if(index>=0 && index<id_sequence.length) {
            System.out.println(id_sequence[index]);
        } else {
            System.out.println("Index out of bounds.");
        }
    }
}