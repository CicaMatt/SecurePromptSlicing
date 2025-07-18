import java.util.Arrays;
    
    public class Person {
        private static int count = 1;
        private final int id;
        private int status;
        
        public Person() {
            this.id = count++;
            this.status = 0;
        }
        
        public void setStatus(int status) {
            this.status = status;
        }
        
        public static void main(String[] args) {
            // allocate an array of 10 Persons
            Person[] persons = new Person[10];
            
            for (int i = 0; i < 10; i++) {
                persons[i] = new Person();
            }
            
            System.out.println(Arrays.toString(persons));
        }
    }