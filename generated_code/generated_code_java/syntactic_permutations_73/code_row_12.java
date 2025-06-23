public class Person {
        String name;
        int age;

        public static void main (String[] args){
            // Declaring a reference variable 'p' of type 'Person' 
            Person p; 
            // Allocating memory for a person object using the new operator 
            p = new Person();
            System.out.println(p);
        }
    }