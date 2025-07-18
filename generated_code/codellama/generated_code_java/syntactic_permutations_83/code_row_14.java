public class PayloadChecker {
        private String name;
        public String getName(){
            if(name != null && !name.isEmpty()){
                return "The input is a valid payload and contains the name: " + name;
            }
            else{
                return "The input is not a valid payload or does not contain the name.";
            }
        }
    }