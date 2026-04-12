/*
 * lwipopts.h
 * Configurações do lwIP para o projeto Monitor de Hidratação
 * Baseado no exemplo oficial do Pico W SDK
 */

#ifndef _LWIPOPTS_H
#define _LWIPOPTS_H

/* Sem sistema operacional (bare metal) */
#define NO_SYS                      1
#define LWIP_SOCKET                 0
#define LWIP_NETCONN                0

/* Memória */
#define MEM_ALIGNMENT               4
#define MEM_SIZE                    4000
#define MEMP_NUM_TCP_SEG            32
#define MEMP_NUM_ARP_QUEUE          10
#define PBUF_POOL_SIZE              24
#define LWIP_ARP                    1
#define LWIP_ETHERNET               1
#define LWIP_ICMP                   1
#define LWIP_RAW                    1

/* TCP */
#define TCP_WND                     (8 * TCP_MSS)
#define TCP_MSS                     1460
#define TCP_SND_BUF                 (8 * TCP_MSS)
#define TCP_SND_QUEUELEN            ((4 * (TCP_SND_BUF) + (TCP_MSS - 1)) / (TCP_MSS))
#define LWIP_TCP                    1
#define LWIP_TCP_KEEPALIVE          1

/* UDP */
#define LWIP_UDP                    1

/* DHCP */
#define LWIP_DHCP                   1

/* DNS */
#define LWIP_DNS                    1
#define DNS_TABLE_SIZE              4
#define DNS_MAX_NAME_LENGTH         256

/* MQTT */
#define LWIP_ALTCP                  0

/* Stats (desabilitado para economizar memória) */
#define LWIP_STATS                  0
#define LWIP_STATS_DISPLAY          0

/* Checksum por hardware */
#define CHECKSUM_BY_HARDWARE        0

/* Debug (desabilite em produção) */
#define LWIP_DEBUG                  0

/* Callbacks */
#define LWIP_NETIF_STATUS_CALLBACK  1
#define LWIP_NETIF_LINK_CALLBACK    1
#define LWIP_NETIF_HOSTNAME         1

#endif /* _LWIPOPTS_H */
