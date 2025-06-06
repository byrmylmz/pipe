#include <stdio.h>      // Giriş/çıkış işlemleri için
#include <stdlib.h>     // Genel amaçlı işlevler (örneğin: exit)
#include <string.h>     // String işlemleri için (gerekli olmasa da çoğu zaman eklenir)
#include <unistd.h>     // sleep() gibi POSIX sistem çağrıları için
#include <pthread.h>    // pthread (POSIX thread) fonksiyonları için

// Global thread tanımı – iki adet thread oluşturacağız
pthread_t tid[2];

// Thread fonksiyonu – her thread çalıştığında bu fonksiyon çağrılır
// bir is parcacigi fonksiyonu.
//void* bir isaretci pointer. her turlu veri tutabilr int*, char*, struct*
void* doSomeThing(void* arg){ 

    // Thread’in kendi ID’sini alıyoruz
    pthread_t id = pthread_self();

    // Thread’i 10 saniye uyutuyoruz (simülasyon amacıyla)
    sleep(5);

    // Hangi thread'in çalıştığını belirliyoruz
    if(pthread_equal(id,tid[0])){
        printf("first thread processing\n");
    }else{
        printf("second thread processing\n");
    }

    // Fonksiyon sonunda NULL döndürülüyor
    return NULL;
}


int main(void) {
    // İlk thread'i oluştur – doSomeThing fonksiyonunu çalıştıracak
    //tid threading idsini verdik
    //NULL varsayilan ozellikler kullanilacak
    //doSomething threadin calistiracagi fonk.
    //NULL Fonstioyone gonderilecek agruman gerekirse.
    //pthread_create - threade arguman gonderip donus almak icin kullanilan fonk.
    pthread_create(&tid[0], NULL, doSomeThing, NULL);
    printf("Thread 1 created\n");

    // İkinci thread'i oluştur
    pthread_create(&tid[1], NULL, doSomeThing, NULL);
    printf("Thread 2 created\n");

    // Ana süreç (main) her iki thread'in tamamlanmasını bekliyor
    //join -Bir thread'in işi bitmeden ana programın veya diğer thread'lerin devam etmesini engellemek.
    //pthread_join() çağrılmazsa, thread bitse bile sistem onun kaynaklarını tamamen temizlemez (zombi thread gibi kalır).
    //Eğer thread bir sonuç döndürüyorsa, pthread_join() ile bu sonucu alabilirsin.
    //bu threadler paralellemi concurrency mi calisacak ona os karar verir
    //nproc - linuxta 1 ise sadece concurrency 2 ise veya daha fazla parallik mumkun ama os karar verir.
    /**
     * bu threadler baslangic ve bitisi cpu nun musaitlik durumuna gore degisir.
     * Bazen second thread ilk calisir, bazen first thread.
     */
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    // Tüm thread’ler bitince bu mesaj yazılır
    printf("Threads done!\n");

    return 0;
}