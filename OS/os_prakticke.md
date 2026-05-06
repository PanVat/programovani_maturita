## OS - praktické

---
### 1. Operační systémy

#### a) Kdo a kdy se zalogoval do PC jako druhý poslední
```
last | head -2 | tail -1
```
#### b) Přesměrujte standartní a chybový výstup spuštěného příkazu pro vyhledání všech souborů txt do souboru 1.log a 2.log
```
find / -name "*.txt" > 1.log 2> 2.log
```
#### c) Kolik paměti RAM je v PC
```
free -h
```
#### d) Jaká je GPU v PC
```
lspci | grep -i vga
```
---
### 2. Souborové systémy
#### a) Vytvořte si soubor, na něj vytvořte symbolický link a zkontrolujte počet odkazů k souboru
```
touch soubor.txt
ln -s soubor.txt link.txt
ls -l soubor.txt
```

#### b) Zprovozněte nový fyzický disk a zajistěte trvalé namapování do Linuxu pro používání?
```
lsblk
sudo fdisk /dev/sda
g, n, ENTER, ENTER, ENTER, w
sudo mkfs.ext4 /dev/sda1
sudo mkdir -p /mnt/disk
sudo blkid /dev/sda1                                       <-- zkopírujeme UUID
sudo nano /etc/fstab
UUID=<tvoje-uuid> /mnt/disk ext4 defaults,nofail 0 2       <-- Přidáme na konec
sudo mount -a
sudo chown $USER:$USER /mnt/disk
df -h                                                      <-- zkontrolujeme, že je disk namapován
```
---
### 3. Správa uživatelů
#### a) Vytvořte uživatele u1, u2, u3, skupinu grp a přiřaďte u1 do grp
```
useradd -m u1 
useradd -m u2
useradd -m u3
groupadd grp
usermod -aG grp u1
```
#### b) Vytvořte adresář adresar v domovském adresáři uživatele u1 a v něm soubor dokument. Nastavte práva na složku adresar následovně: 
#### - u2 vlastník s právy čtení, zápis, list/spouštět </br> - grp má čtení, zápis </br> - ostatní mohou číst </br> - u3 nemá žádné právo
```
sudo -u u1 mkdir /home/u1/adresar
sudo -u u1 touch /home/u1/adresar/dokument
sudo chown u2:grp /home/u1/adresar
sudo chmod 770 /home/u1/adresar
sudo setfacl -m u:u3:--- /home/u1/adresar
```
#### c) Vyhledejte zadaný soubor na disku
```
sudo find / -name "soubor.txt"
```
---
### 4. Správa procesů
#### a) Vyhledejte proces nejvíce využívající operační paměť
```
ps aux --sort=-%mem | head -2
```
#### b) Snižte prioritu na minimum u procesu nejvíce vytěžujícího cpu
```
ps aux --sort=-%cpu | head -2           <-- Zjistíme PID procesu
sudo renice -n 19 -p <PID>
```
#### c) Spusťte proces s prioritou 14
```
sudo nice -n 14 <příkaz>
```
#### d) Ukončete všechny podprocesy aplikace Pluma
```
pkill pluma
```
---
### 5. Služby
#### a) Zjistěte, které následující služby jsou spuštěné (cups, ufw, telnet)
```
systemctl status cups
systemctl status ufw
systemctl status telnet
```
#### b)	Zajistěte, aby po restartu PC, nebyla služba ufw spuštěna a udělejte aktualizace OS
```
sudo systemctl disable ufw
sudo apt update && sudo apt upgrade -y
```
#### c) Znova načtěte konfiguraci procesu cups bez jeho restartu
```
sudo systemctl reload cups
```
---
### 6. Skripty v Linuxu
#### a) Pravidelně denně ve 03:00 zálohujte adresář /home/u1/Plocha do složky, jež je uvedena jako první parametr skriptu
```
#!/bin/bash

# Kontrola, zda uživatel zadal cílovou složku jako parametr
if [ -z "$1" ]; then
    echo "Chyba: Musíš zadat cílovou složku jako první parametr!"
    exit 1
fi

CIL="$1"
ZDROJ="/home/u1/Plocha"
DATUM=$(date +%Y-%m-%d)

# Vytvoření cílové složky, pokud neexistuje
mkdir -p "$CIL"

# Vytvoření komprimované zálohy (archivu .tar.gz)
tar -czf "$CIL/zaloha_plocha_$DATUM.tar.gz" "$ZDROJ"

echo "Záloha byla úspěšně vytvořena v $CIL"
```
```
crontab -e
00 03 * * * /cesta/ke/skriptu/zaloha.sh /mnt/disk/zalohy
```