import org.springframework.web.bind.annotation.*;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;

@RestController
public class StockController {
 
   @GetMapping("/stock_form")
    public String stockForm(Model model) {
        return "stock_form";
    }
 
    @PostMapping("/buy_order")
    public String buyOrder(@RequestParam("stockName") String stockName, @RequestParam("quantity") int quantity) {
        // Code to insert the data into the database goes here
        model.addAttribute(stockName);
        return "stock_view";
    }
}