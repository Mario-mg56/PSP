package sockets03.tcp;

import java.time.LocalDate;
import java.io.Serializable;

public class Bill implements Serializable{
    String billId;
    LocalDate date;
    float importe, ivaAmount, totalAmount;
    IVA iva;
    public Bill(String billId, LocalDate date, float importe, IVA iva) {
        this.billId = billId;
        this.date = date;
        this.importe = importe;
        this.iva = iva;
    }

    public void calculate() {
        switch (iva) {
            case IGC:
                ivaAmount = 0.07f*importe;
                break;
            case ESP:       
                ivaAmount = 0.21f*importe;
                break;
            case EUR:   
                ivaAmount = 0.15f*importe;   
        }
        totalAmount = importe + ivaAmount;
    }

    enum IVA {IGC, ESP, EUR}
}
