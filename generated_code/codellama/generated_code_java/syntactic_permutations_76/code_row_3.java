import java.util.Scanner;
    class Person {
        int age;
        String name;
    }

    public class Main {
        static Scanner scn = new Scanner(System.in);
        public static void main(String[] args) {
            System.out.print("Enter the person's name: ");
            Person p = new Person();
            p.name = scn.nextLine();

            System.out.print("Enter the person's age: ");
            p.age = scn.nextInt();
        }
    }