
# Sosyal Ağ Analizi ve Red-Black Tree Kullanımı

Bu proje, kullanıcılar arasındaki arkadaşlık ilişkilerini modelleyerek sosyal ağ analizi yapmayı amaçlar. Kullanıcılar ve arkadaşlık ilişkileri bir **graf** yapısı ile temsil edilirken, **red-black tree** veri yapısı kullanılarak kullanıcı aramaları ve eklemeleri optimize edilmiştir. Ayrıca topluluk tespiti, ortak arkadaş analizi ve etki alanı hesaplama gibi sosyal ağ analizleri yapılmaktadır.

## Özellikler

- **Red-Black Tree**: Kullanıcı kimliklerine göre dengeleme sağlayarak, kullanıcı eklemeleri ve aramaları hızlı ve etkili bir şekilde yapılır.
- **Sosyal Ağ Modeli (Graf)**: Kullanıcılar ve arkadaşlık ilişkileri, bir bağlantı matrisi kullanılarak bir **graf** yapısında saklanır.
- **Topluluk Tespiti**: Kullanıcılar arasındaki ilişkilerden bağımsız gruplar (topluluklar) tespit edilir.
- **Arkadaş Analizi**: Bir kullanıcıyla doğrudan ve dolaylı (mesafe 2) ilişkide olan arkadaşlar, ortak arkadaşlar ve etki alanı hesaplanır.

## Kullanılan Teknolojiler

- **C Programlama Dili**
- **Red-Black Tree (Dengeleme ve Arama Yapısı)**: Kullanıcı kimliklerinin dengeli bir şekilde saklanmasını sağlar.
- **Graf Veri Yapısı**: Kullanıcılar arasındaki ilişkiler (arkadaşlıklar) bir bağlantı matrisi ile modellenir.

## Proje Yapısı

Projenin temel bileşenleri şunlardır:

1. **Red-Black Tree**:
    - Kullanıcı kimliklerini depolamak için kullanılan dengeli bir ağaç yapısıdır.
    - Bu yapı, kullanıcı ekleme ve arama işlemlerini hızlı bir şekilde gerçekleştirir.
    - Her düğüm, kullanıcı ID'sini tutar ve ağacın renkli düğüm yapısı, ağacın dengesini korur.

2. **Graf Veri Yapısı**:
    - Kullanıcılar arasındaki arkadaşlık ilişkileri, bir **adjacency matrix** (bağlantı matrisi) kullanılarak saklanır.
    - Bu matris, her bir kullanıcı ile diğer kullanıcılar arasındaki arkadaşlık ilişkisini temsil eder.

3. **Sosyal Ağ Analiz Fonksiyonları**:
    - **DFS (Depth-First Search)**: Kullanıcılar arasındaki bağlantıları incelemek ve toplulukları tespit etmek için derinlik öncelikli arama kullanılır.
    - **Ortak Arkadaşlar**: İki kullanıcı arasındaki ortak arkadaşlar bulunur.
    - **Topluluk Tespiti**: Sosyal ağda birbirleriyle bağlı olan gruplar (topluluklar) tespit edilir.
    - **Etki Alanı Hesaplama**: Bir kullanıcının ağ üzerindeki etkisi, kendisine doğrudan bağlı olan ve dolaylı olarak etkileşimde bulunduğu kişiler ile ölçülür.

## Kurulum ve Çalıştırma

### Gereksinimler

- **C derleyicisi** (GCC, Clang vb.)
- **Basit bir metin editörü** (VSCode, Sublime Text, Notepad++ vb.)

### Adımlar

1. **Proje Dosyasını İndirin**:  
   Projeyi bilgisayarınıza indirmeniz gerekmektedir. Aşağıdaki komut ile GitHub reposunu klonlayabilirsiniz:

   ```bash
   git clone https://github.com/fsudesnmz/repository-sosyal-ag-analiz-sistemi.git
   ```

2. **Veriseti Dosyasını Oluşturun**:  
   `veriseti.txt` dosyasını proje dizinine ekleyin. Dosya, kullanıcıları ve arkadaşlık ilişkilerini şu formatta içermelidir:

   ```
   USER 101
   USER 102
   USER 103
   USER 104
   USER 105

   FRIEND 101 102
   FRIEND 101 103
   FRIEND 102 104
   FRIEND 103 104
   FRIEND 104 105
   ```

   - **USER** satırları kullanıcıları tanımlar.
   - **FRIEND** satırları kullanıcılar arasındaki arkadaşlık ilişkilerini belirtir.

3. **Proje Derleme**:  
   Projeyi derlemek için aşağıdaki komutları kullanabilirsiniz (GCC kullanarak):

   ```bash
   gcc main.c -o social_network
   ```

4. **Programı Çalıştırma**:  
   Derledikten sonra, programı çalıştırmak için:

   ```bash
   ./social_network
   ```

   Program, `veriseti.txt` dosyasını okuyacak ve sosyal ağ analizini yaparak çıktı verecektir.

### Çıktılar

Program çalıştırıldığında, aşağıdaki analiz sonuçları terminalde görüntülenir:

1. **Doğrudan Arkadaşlar (Mesafe 1)**: Bir kullanıcının doğrudan arkadaşları listelenir.
2. **Mesafe 2 Arkadaşlar**: İki derece mesafedeki arkadaşlar (yani, kullanıcının arkadaşlarının arkadaşları) listelenir.
3. **Ortak Arkadaşlar**: İki kullanıcı arasındaki ortak arkadaşlar belirlenir.
4. **Etki Alanı**: Bir kullanıcının erişebildiği toplam kişi sayısı hesaplanır (etkileşimde bulunabileceği kullanıcılar).

Ayrıca, **topluluk tespiti** yapılır ve sosyal ağda birbirine bağlı bağımsız gruplar (topluluklar) tespit edilir.

## Red-Black Tree Hakkında

Red-Black Tree, ikili arama ağacının özel bir türüdür ve şu özelliklere sahiptir:

- Her düğüm ya kırmızı ya da siyah renkli olmalıdır.
- Kök düğüm her zaman siyah renkte olmalıdır.
- Kırmızı düğümlerin çocukları her zaman siyah renkte olmalıdır.
- Herhangi bir düğümden kök düğümüne giden her yol, eşit sayıda siyah düğüm içermelidir.

Bu özellikler, ağacın dengede kalmasını sağlar ve bu sayede **ekleme**, **silme** ve **arama** işlemleri ortalama `O(log n)` zaman karmaşıklığına sahiptir.

Bu projede, kullanıcı kimliklerini depolamak ve aramak için **Red-Black Tree** kullanılmaktadır. Bu sayede kullanıcı ekleme işlemleri hızlı bir şekilde yapılabilir ve aynı zamanda dengeleme sayesinde ağacın derinliği minimal tutulur.

## Sosyal Ağ Analizi ve DFS

Projedeki sosyal ağ yapısında, kullanıcılar arasındaki arkadaşlıklar bir **graf** yapısı kullanılarak modellenmiştir. Kullanıcılar arasındaki ilişkiler, **adjacency matrix** (bağlantı matrisi) ile saklanır. Her kullanıcının bağlantılarını bu matris üzerinden takip edebiliriz.

- **DFS (Depth-First Search)**, graf üzerinde derinlik öncelikli arama yaparak, bir kullanıcı ile doğrudan veya dolaylı olarak bağlantılı diğer kullanıcıları keşfeder. Bu, özellikle **topluluk tespiti** ve **etki alanı hesaplama** gibi analizlerde kullanılır.

## Lisans

Bu proje, **MIT Lisansı** ile lisanslanmıştır.

