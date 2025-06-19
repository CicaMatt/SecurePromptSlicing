public class Main {
        public static void main(String[] args) {
            Person p = new Person();
            p.setName("John");
            p.setStatus(0);
        }
    }
    
    class Person{
        String name;
        int status;
        public void setName(String n){
            this.name=n;
        }
        public void setStatus(int s){
            this.status=s;
        }
    }