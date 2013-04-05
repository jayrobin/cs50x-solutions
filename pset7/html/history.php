<?php

    // configuration
    require("../includes/config.php"); 
    
    if(isset($_SESSION["id"]))
    {
        
        // get users transactions
        $rows = query("SELECT * FROM transactions WHERE id = ?", $_SESSION["id"]);
        if(count($rows) > 0)
        {
            $transactions = [];
            foreach($rows as $row)
            {
                $transactions[] = [
                    "transaction" => $row["transaction"],
                    "datetime" => $row["datetime"],
                    "symbol" => $row["symbol"],
                    "shares" => $row["shares"],
                    "price" => money_format("$%i", $row["price"])
                ];
            }
            render("history_table.php", ["title" => "History", "transactions" => $transactions]);
        }
        else
        {
            render("history_table.php", ["title" => "History"]);
        }
    }

?>
