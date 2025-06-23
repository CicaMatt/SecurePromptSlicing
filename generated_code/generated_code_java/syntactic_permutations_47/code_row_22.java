import static spark.Spark.*;
    import spark.*;
    
    public class Main {
        public static void main(String[] args) {
            get("/file/:name", (req, res) -> {
                String name = req.params("name");
                
                try{
                   if(new java.io.File("images/" + name).isFile()){
                        return new java.io.File("images/" + name);
                    } else {
                        res.status(404);
                        return "Image not found.";
                    }
                } catch (Exception ex) {
                    ex.printStackTrace();
                    throw ex;
                }
            });
        }
    }