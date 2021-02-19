<div align="center">

# Sol Lewitt 1136

<img width="800px" src="docs/imgs/header.png">

</div>

## Overview

The Sol Lewitt 1136 app is a digital recreation of Sol Lewitt's <em>Wall Drawing 1136</em> that allows the user to "paint" their own version to an infinite canvas. For reference, the "original" (see [Background](#Background)) can be found at the [Scottish National Gallery of Modern Art](https://www.nationalgalleries.org/exhibition/artist-rooms-sol-lewitt-wall-drawing-1136-2004).

## Background 

[Sol Lewitt](https://en.wikipedia.org/wiki/Sol_LeWitt) (1928 – 2007) was an American visual artist. Among his most famous works are his <em>Wall Drawings</em>, mural paintings consisting of simple figures or patterns covering large wall segments. In most cases, the actual "work" consists of a small piece of paper with diagrams or algorithm-like instructions detailing how to create the painting. The murals are then created by teams of draftsmen following or interpreting the instructions. An example of his instructions can be found accompanying <em>Wall Drawing 118</em>:

  
  >       On a wall surface, any
  >       continuous stretch of wall,
  >       using a hard pencil, place
  >       fifty points at random.
  >       The points should be evenly
  >       distributed over the area
  >       of the wall. All of the
  >       points should be connected
  >       by straight lines.


In many cases, the instructions themselves are not public, but some rules can be inferred by observing the drawings closely. In the case of <em>Wall Drawing 1136</em>, it appears that each color is to be separated by at least two other colors before it is repeated. This informs the color selection algorithm in the app as the canvas advances and new wall strips are generated.

Many other examples of digital versions of the <em>Wall Drawings</em> can be found at the [Solving Sol](https://github.com/wholepixel/solving-sol) project, an open source collection of implementations of Lewitt's work in Javascript. 

## Install

The app can be downloaded from the [Releases page](https://github.com/michaelnuzzo/Sol-Lewitt-1136/releases) in this repository. You may need to authorize the app to be run on your machine in "System Preferences -> Security & Privacy -> General -> Allow apps downloaded from".

Currently, the only available binary is for macOS. If you would like to generate a binary for your platform, please see [Build][(Build).

## Build

The Sol Lewitt 1136 app was built in openFrameworks. You should be able to build the .app by creating a new openFrameworks project and installing the files in the src/ directory.
