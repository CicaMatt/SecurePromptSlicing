public class Person {
        private String name;
        private int age;
        private boolean isAlive = false;
     
        public void setName(String name){
            this.name = name;
        }
     
        public String getName(){
            return name;
        }
     
        public void setAge(int age){
            this.age = age;
        }
     
        public int getAge(){
            return age;
        }   
    
        public boolean getIsAlive(){
            return isAlive;
        }
    }