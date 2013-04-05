<form action="sell.php" method="post">
    <fieldset>
        <div class="control-group">
            <select name="symbol">
                <option value=''></option>
                <?php
                    foreach($positions as $position)
                    {
                        print("<option value='" . $position["symbol"] . "'>" . $position["symbol"] . "</option>");
                    }
                ?>
            </select>
        </div>
        <div class="control-group">
            <button type="submit" class="btn">Sell</button>
        </div>
    </fieldset>
</form>
