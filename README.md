Kristal Salju Menggunakan ROS 2 dan Turtlesim

Deskripsi Program
Program ini dibuat menggunakan bahasa pemrograman C++ dan ROS 2 untuk menggambar pola kristal salju pada simulasi Turtlesim. Program mengendalikan pergerakan Turtle melalui perintah kecepatan linear dan sudut yang dikirimkan menggunakan publisher ROS 2. Konsep utama yang digunakan dalam program ini meliputi publisher, pesan Twist, pergerakan linear dan rotasi, perulangan (looping), serta rekursi (recursion) untuk membentuk pola geometris berulang.

Penjelasan Kode
1. Library dan Header
Program menggunakan beberapa library, yaitu chrono, functional, dan memory, serta header ROS 2 rclcpp dan geometry_msgs/msg/twist.hpp. Library tersebut mendukung pengelolaan waktu, pembuatan objek, dan komunikasi dengan ROS 2. Tipe pesan geometry_msgs::msg::Twist digunakan untuk mengatur kecepatan linear dan kecepatan sudut Turtle. Sementara itu, rclcpp digunakan untuk membuat node dan publisher.

2. Class KristalSalju
Class KristalSalju merupakan turunan dari rclcpp::Node dan berfungsi sebagai node ROS 2 yang mengendalikan pergerakan Turtle. Pada constructor, node diberi nama kristal_salju. Publisher dibuat untuk mengirimkan pesan bertipe Twist ke topik /turtle1/cmd_vel, sehingga perintah gerakan dapat diterima oleh Turtle pertama pada Turtlesim. Program juga memberikan jeda selama satu detik sebelum proses menggambar dimulai.

3. Fungsi move()
Fungsi move() digunakan untuk menggerakkan Turtle maju atau mundur berdasarkan kecepatan dan jarak yang ditentukan. Fungsi ini memiliki tiga parameter, yaitu speed untuk menentukan kecepatan gerak, distance untuk menentukan jarak tempuh, dan forward untuk menentukan arah gerakan. Pergerakan dilakukan dengan mengirimkan pesan kecepatan secara berulang melalui publisher. Jarak tempuh diperkirakan berdasarkan kecepatan linear dikalikan waktu yang telah berlalu. Ketika jarak yang ditentukan tercapai, kecepatan linear diatur menjadi nol agar Turtle berhenti.

4. Fungsi rotate()
Fungsi rotate() digunakan untuk memutar Turtle berdasarkan kecepatan sudut dan besar sudut yang ditentukan. Parameter speed_deg menentukan kecepatan putaran dalam derajat per detik, sedangkan angle_deg menentukan besar sudut putaran. Parameter clockwise digunakan untuk menentukan arah putaran, yaitu searah atau berlawanan arah jarum jam. Karena ROS 2 menggunakan radian untuk kecepatan sudut, nilai dalam derajat dikonversi menjadi radian menggunakan konstanta pi. Selanjutnya, pesan kecepatan sudut dikirimkan secara berulang hingga sudut yang dituju tercapai. Setelah itu, kecepatan sudut diatur menjadi nol.

5. Fungsi gambar_sisi()
Fungsi gambar_sisi() merupakan bagian utama yang membentuk pola kristal salju dengan menggunakan konsep rekursi (recursion). Rekursi adalah teknik pemrograman ketika sebuah fungsi memanggil dirinya sendiri untuk menyelesaikan tugas secara bertahap. Fungsi ini memiliki tiga parameter, yaitu length untuk menentukan panjang sisi, depth untuk menentukan kedalaman rekursi, dan speed untuk menentukan kecepatan gerakan Turtle. Ketika nilai depth sama dengan nol, fungsi akan memanggil move() untuk menggerakkan Turtle secara lurus. Namun, jika nilai depth masih lebih besar dari nol, panjang sisi dibagi menjadi tiga bagian dan fungsi memanggil dirinya sendiri dengan nilai depth yang dikurangi satu. Di antara pemanggilan rekursif tersebut, Turtle melakukan rotasi sebesar 60° atau 120° untuk membentuk pola zig-zag. Proses ini diulang hingga mencapai kondisi dasar. Dengan kedalaman rekursi sebesar 2, setiap sisi awal menghasilkan 16 segmen garis kecil.

6. Fungsi gambar_KristalSalju()
Fungsi gambar_KristalSalju() bertugas mengatur proses menggambar pola utama. Fungsi ini memiliki parameter length dengan nilai awal 4.5 dan depth dengan nilai awal 2. Pada awal proses, program menampilkan pesan bahwa proses menggambar dimulai. Selanjutnya, perulangan for digunakan untuk menjalankan fungsi gambar_sisi() sebanyak tiga kali. Setelah setiap sisi selesai digambar, Turtle diputar sebesar 120° searah jarum jam untuk mengubah arah gerak. Setelah seluruh pengulangan selesai, program menampilkan pesan bahwa proses menggambar telah berakhir.

7. Variabel Publisher
Variabel publisher_ dideklarasikan pada bagian private dengan tipe rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr. Variabel ini menyimpan objek publisher yang digunakan oleh fungsi move() dan rotate() untuk mengirimkan perintah gerakan ke topik /turtle1/cmd_vel.

8. Fungsi main()
Fungsi main() merupakan titik awal eksekusi program. Pertama, ROS 2 diinisialisasi menggunakan rclcpp::init(). Kemudian, objek dari class KristalSalju dibuat menggunakan make_shared. Setelah objek berhasil dibuat, fungsi gambar_KristalSalju(4.5, 2) dipanggil untuk memulai proses menggambar dengan panjang sisi awal 4.5 dan kedalaman rekursi 2

Link Video :
