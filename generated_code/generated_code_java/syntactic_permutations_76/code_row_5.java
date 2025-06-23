public class Person {
        private int status;
        public static Person allocate() {
            return new Person();
        }
    }