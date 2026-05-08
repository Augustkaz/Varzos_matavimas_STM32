# Varzos_matavimas_STM32

STM32 Dual-Channel Resistance Meter
Tai dviejų kanalų varžos matuoklis, sukurtas naudojant STM32L073RZT6 mikrovaldiklį, OLED ekraną ir įtampos daliklio metodą.

* **Matavimo diapazonas:** nuo 0,1 Ω iki 10 kΩ.
* **Kanalai:** 2 nepriklausomi matavimo kanalai + automatinis vidurkio skaičiavimas.
* **Skaitmeninis triukšmų slopinimas (DSP):** Naudojamas aparatūrinis TIM6 laikmatis, kuris užtikrina tikslų ADC nuskaitymą kas 25 ms. 20 mėginių surenkami per 0,5 s langą
* **Atvaizdavimas:** Rezultatai atnaujinami SSD1306 OLED ekrane kas 0,5 s.
* **Duomenų perdavimas:** UART sąsaja (115200 bps) kas 1 s siunčia suformatuotus duomenis į kompiuterį (su „OL“ – *Open Line* apsauga).
Blokinė diagrama
<img width="1101" height="357" alt="image" src="https://github.com/user-attachments/assets/78c3f47d-ae29-4b86-898e-fe6ca60ca666" />

Programinė dalis (software)
<img width="703" height="1043" alt="image" src="https://github.com/user-attachments/assets/e46f7617-52d2-45e8-9b91-cc30f702694d" />

## 🛠 Aparatūra (BOM)

Projektui įgyvendinti naudoti šie komponentai:
* **Mikrovaldiklis:** NUCLEO-L073RZ (STM32L073RZT6)
* **Ekranas:** 0.91" OLED modulis (SSD1306, I2C)
* **Etaloniniai rezistoriai ($R_{ref}$):** 2 vnt. x 1 kΩ (1% tolerancija)
* RC filtrai (100 nF kondensatoriai), testuojami rezistoriai, jungiamosios kaladėlės.
  
## 🔌 Pajungimo schema (Pinout)

| Mikrovaldiklio Pin'as | Funkcija | Prijungta prie |
| :--- | :--- | :--- |
| **PA0** | ADC_IN0 | 1-ojo kanalo matavimo taškas ($R_{x1}$) |
| **PA1** | ADC_IN1 | 2-ojo kanalo matavimo taškas ($R_{x2}$) |
| **PB8** | I2C1_SCL | OLED ekrano SCL (Clock) |
| **PB9** | I2C1_SDA | OLED ekrano SDA (Data) |
| **PA2** | USART2_TX | Duomenų siuntimas į PC (VCP) |
| **PA3** | USART2_RX | Duomenų gavimas iš PC (VCP) |
| **3V3 / GND** | Maitinimas | OLED, $R_{ref}$ ir RC filtrai |

STM32CubeMx Pinout
<img width="834" height="905" alt="image" src="https://github.com/user-attachments/assets/df407c6b-6baa-4b16-9a54-90b8d6d74694" />

Principinė schema
<img width="1454" height="749" alt="image" src="https://github.com/user-attachments/assets/811f75ee-a285-48d5-a1da-2194418958ed" />

## 📈 Veikimo principas ir tikslumas

Matavimas paremtas klasikiniu įtampos daliklio dėsniu. Kadangi mikrovaldiklis matuoja įtampą skaitmeniniais ADC vienetais (12-bit, nuo 0 iki 4095), varža apskaičiuojama pagal išvestą formulę:
`Rx = Rref * (ADC_išmatuotas / (4095 - ADC_išmatuotas))`

**Testavimo rezultatai:**
Sistema demonstruoja itin aukštą tikslumą matuojant varžas, artimas etaloniniam 1 kΩ rezistoriui. 
* Matuojant 995 Ω varžą, santykinė paklaida yra vos **0,02 %**. 
* Matuojant viso diapazono ribose (0,1 Ω – 10 kΩ), vidutinė paklaida išlieka inžineriškai priimtinose ribose (~1,5 %), didesni nuokrypiai atsiranda tik pačiuose diapazono kraštuose dėl fizinių 12-bit ADC rezoliucijos ribų.

Tikslumas ir testavimo rezultatai (Performance)
<img width="748" height="465" alt="image" src="https://github.com/user-attachments/assets/3f84bcaf-663e-4620-aaa3-b5fb58779a98" />
testavimo metu gautos vertės ir apskaičiuotos paklaidos

<img width="609" height="386" alt="image" src="https://github.com/user-attachments/assets/e4bbf7a4-9768-4a53-895d-8b7048bb576a" />
Santykinė paklaida kintant matuojamai varžai.

