
/*
 * Shah Nawaz Khan
 * shah-nawaz.khan@tu-ilmenau.de
 *
 * An RTS/CTS based Mac implementation that is connected with Spectrum Sensing Module and can avoid Primary Users by switching channels. Channel switching/mobility
 * is based on the recommendation of DRM component
 */

#ifndef DRMMACLAYER_H_
#define DRMMACLAYER_H_

#include "BaseMacLayer.h"
#include "ctrlMsg_m.h"
#include "dataMsg_m.h"
#include "timerMsg_m.h"

class drmMacLayer : public BaseMacLayer {

private:
        int numberOfPackets, totalFrames;  // The number of packets to send in response to Application request.
        bool perPacketSensing;   // Should the transmission channel be sensed per packet or per session
        bool drmEnabled;
        bool ackEnabled;


    int myAddress;  // MAC address of node
    int currentDestination;  // Keeps track on next hop or destination
    int currentDataChannel;    // The channel currently used for data transmission.
    int proposedChannel;
    int drmChannel;
    bool rtsSent;         // to keep track of sent RTS
    timerMsg *rtsTimer, *ackTimer;   // RTS timer for next attempt and ACK timeout
    bool isReceiving, isTransmitting;   // keeps track of radio state
    int rtsAttempts, ctsDestination; // keeps track of number of retransmissions.

    // Statistics
    simsignal_t rtsSignal, dataSignal;
    simsignal_t handover;
    simsignal_t nackSignal;

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();

    // Msg sending functions
    void sendRTS(int);
    void sendCTS();
    void sendData();
    void sendAck();
    void sendNack(int);
    void sendEOT();     // Indicates the end of transmission or contention

    // Msg handling functions
    void handleRTS(dataMsg *msg);
    void handleCTS(dataMsg *msg);
    void handleData(dataMsg *msg);
    void handleAck();
    void handleNack(int);
    void handleEOT();
    void handlePU();

    // Timer Setting/Clearing functions
    void setRTStimer();
    void clearRTStimer();
    void clearAckTimer();
    void setAckTimeOut();

    // Objective functions
    void senseRequest(int);
    void getIdle();
    void notifyAppLayer(int);    // 0 as failure 1 as success
};

Define_Module(drmMacLayer);

#endif /* DRMMACLAYER_H_ */
