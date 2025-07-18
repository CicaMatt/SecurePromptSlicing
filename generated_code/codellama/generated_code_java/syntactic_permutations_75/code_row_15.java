public class Person {
        private String name;
        private int age;
        private char gender;
    
        public static void main(String[] args) {
            // allocate memory for a person object
            Person p = (Person)allocateMemory();
        
            // initialize fields of the person object
            p.name = "John Doe";
            p.age = 30;
            p.gender = 'M';
        }
    
        private static Object allocateMemory() {
            return new Person();
        }
    }