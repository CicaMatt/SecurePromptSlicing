import java.util.*;

    public class Person {
        private int status = 0;
        
        private static List<Person> people = new ArrayList<>();
        
        public void setStatus(int status) {
            this.status = status;
        }
        
        public void allocate() {
            Person person = new Person();
            people.add(person);
        }
    }