@RequestMapping(value = "buy_order", method=RequestMethod.POST)
public String buyOrder(@RequestParam String stockName, @RequestParam Integer quantity){
    //code for inserting the data in the database
    return "redirect:/stock_view";
}